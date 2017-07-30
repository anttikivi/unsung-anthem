# utils/update_checkout.py - Utility to update local checkouts ----*- python -*-
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

from __future__ import print_function

import contextlib
import json
import os
import platform
import tarfile
import zipfile

from multiprocessing import freeze_support

import sys

import requests

from . import diagnostics, github, shell

from products import llvm

from variables import ANTHEM_SOURCE_ROOT

VERSIONS_FILE = os.path.join(ANTHEM_SOURCE_ROOT, 'versions')


def parse_git_version(version):
    if version.startswith("commit:"):
        ret = version.split(':')[1]
    elif version.startswith("commit="):
        ret = version.split('=')[1]
    elif version.startswith("commit "):
        ret = version.split(' ')[1]
    elif version.startswith("branch:"):
        ret = version.split(':')[1]
    elif version.startswith("branch="):
        ret = version.split('=')[1]
    elif version.startswith("branch "):
        ret = version.split(' ')[1]
    else:
        ret = version

    return ret


def is_commit(version):
    return version.startswith("commit:") or version.startswith("commit=") \
        or version.startswith("commit ")


def is_branch(version):
    return version.startswith("branch:") or version.startswith("branch=") \
        or version.startswith("branch ")


def is_git_version(version):
    return is_commit(version) or is_branch(version) or version == "git"


def move_files(key, version):
    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'),
                   os.path.join(ANTHEM_SOURCE_ROOT, key, version))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))


def move_source_files(key, version, owner, repository, sha):
    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                key,
                                'temp',
                                owner + '-' + repository + '-' + sha),
                   os.path.join(ANTHEM_SOURCE_ROOT, key, version))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))


def move_llvm_files(args, key, directory):
    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(llvm.get_project_directory(args, key))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(llvm.get_temp_directory(key), directory),
                   llvm.get_project_directory(args, key))

    # Delete the temporary folder.
    shell.rmtree(llvm.get_temp_directory(key))


def move_gcc_files(args, directory):
    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', args.gcc_version))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp', directory),
                   os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', args.gcc_version))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp'))


def move_cmake_files(args, key, directory):
    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, args.cmake_version))

    # On Darwin, the CMake.app may have some other name so it has to be renamed
    # to CMake.app.
    if platform.system() == 'Darwin':
        cmake_app = os.listdir(os.path.join(ANTHEM_SOURCE_ROOT,
                                            key,
                                            'temp',
                                            directory))[0]

        shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                    key,
                                    'temp',
                                    directory,
                                    cmake_app),
                       os.path.join(ANTHEM_SOURCE_ROOT,
                                    key,
                                    args.cmake_version,
                                    'CMake.app'))
    else:
        # Copy the files from the temporary folder to the correct folder.
        shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                    key,
                                    'temp',
                                    directory),
                       os.path.join(ANTHEM_SOURCE_ROOT,
                                    key,
                                    args.cmake_version))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))


def move_sdl_files(args, key, directory):
    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, args.sdl_version))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp', directory),
                   os.path.join(ANTHEM_SOURCE_ROOT, key, args.sdl_version))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))


def move_glfw_files(args):
    # Delete the GLFW folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'glfw', args.glfw_version))

    # Copy the files from the temporary folder to the correct folder.
    if platform.system() == 'Windows':
        shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                    'glfw',
                                    'temp',
                                    'glfw-'
                                    + args.glfw_version
                                    + '.bin.WIN32'),
                       os.path.join(ANTHEM_SOURCE_ROOT,
                                    'glfw',
                                    args.glfw_version))
    else:
        shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                    'glfw',
                                    'temp',
                                    'glfw-'
                                    + args.glfw_version),
                       os.path.join(ANTHEM_SOURCE_ROOT,
                                    'glfw',
                                    args.glfw_version))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'glfw', 'temp'))


def dump_version_info(versions):
    # Write the versions to a JSON file so next time the script can download
    # only the ones that are updated.
    with open(os.path.join(ANTHEM_SOURCE_ROOT, 'versions'), 'w') as outfile:
        json.dump(versions, outfile)


def get_github_dependency(args, toolchain, key, dependency, protocol):
    # If the dependency is cloned via git, the files will be automatically in
    # the correct directory so the function can return after handling the cloning.
    if is_git_version(args.version_info[key]):
        version = parse_git_version(args.version_info[key])

        # Delete the old directory if it exists.
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))

        # Make the directory to which the git repository will be cloned to.
        shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

        # Clone the repository to the directory.
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key)):
            shell.call([str(toolchain.git),
                        'clone',
                        github.GITHUB_GIT_URL.format(owner=dependency['owner'],
                                                     repo=dependency['id']),
                        version])

        if is_commit(args.version_info[key]) \
                or is_branch(args.version_info[key]):
            with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key, version)):
                shell.call([str(toolchain.git), 'checkout', version])

    # Set a shortcut to the asset data.
    asset = dependency['asset']

    version = args.version_info[key]
    version_with_prefix = dependency['version_prefix'] + version

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

    # Check whether the asset has different version on different
    # platforms.
    if asset['multiplatform']:
        if platform.system() in asset.keys():
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name=version_with_prefix,
                                  asset_name=asset[platform.system()],
                                  destination=os.path.join(key,
                                                           'temp',
                                                           asset['id']),
                                  ci=args.ci,
                                  protocol=protocol)
        else:
            if asset['fallback']:
                github.download_asset(owner=dependency['owner'],
                                      repository=dependency['id'],
                                      release_name=version_with_prefix,
                                      asset_name=asset['id'],
                                      destination=os.path.join(key,
                                                               'temp',
                                                               asset['id']),
                                      ci=args.ci,
                                      protocol=protocol)
            else:
                print('Not supported')  # TODO
    else:
        if asset['source']:
            github.download_source(owner=dependency['owner'],
                                   repository=dependency['id'],
                                   release_name=version_with_prefix,
                                   destination=os.path.join(key,
                                                            'temp',
                                                            key
                                                            + '.tar.gz'),
                                   ci=args.ci,
                                   protocol=protocol)
        else:
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name=version_with_prefix,
                                  asset_name=asset['id'],
                                  destination=os.path.join(key,
                                                           'temp',
                                                           asset['id']),
                                  ci=args.ci,
                                  protocol=protocol)

    if asset['source']:
        # Set the asset file for the processing of the file to the
        # downloaded source tarball.
        asset_file = os.path.join(ANTHEM_SOURCE_ROOT,
                                  key,
                                  'temp',
                                  key + '.tar.gz')

        # Open the archive.
        tar = tarfile.open(asset_file, "r:gz")

        # Extract the archive to the correct subdirectory.
        tar.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

        # Close the open file.
        tar.close()

        # Delete the archive as it is extracted.
        shell.rm(asset_file)

        # Get the short SHA of the tag for handling the downloaded  files.
        sha = github.get_release_short_sha(owner=dependency['owner'],
                                           repository=dependency['id'],
                                           release_name=version_with_prefix,
                                           ci=args.ci,
                                           protocol=protocol)

        # Manually move the downloaded sources to the actual directory.
        move_source_files(key=key,
                          version=version,
                          owner=dependency['owner'],
                          repository=dependency['id'],
                          sha=sha)
    else:
        # Set the asset file for the processing of the file.
        asset_file = os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp', asset['id'])

        # Check if the downloaded asset is a zip archive.
        if '.zip' in asset_file:
            diagnostics.note('The downloaded asset is a zip archive. '
                             'Extracting now.')

            # Use Python to extract the archive.
            with contextlib.closing(zipfile.ZipFile(asset_file, 'r')) as z:
                z.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT,
                                               key,
                                               'temp'))

            # Delete the archive as it is extracted.
            shell.rm(asset_file)

        if key != 'glfw':
            move_files(key=key, version=version)

        # Do the manual tasks if this dependency requires them.
        if key == 'glfw':
            move_glfw_files(args)


def get_llvm_dependency_git(args, key, git_url_format, project_git, toolchain):
    # Delete the old directory.
    shell.rmtree(llvm.get_project_directory(args, key))
    shell.rmtree(llvm.get_temp_directory(key))

    # Make a new version directory.
    shell.makedirs(llvm.get_version_directory(args))

    # Clone the git repository.
    with shell.pushd(llvm.get_version_directory(args)):
        shell.call([str(toolchain.git),
                    'clone',
                    git_url_format.format(project=project_git),
                    key])

    # If the version is 5, checkout to the branch of the release.
    if args.llvm_version.startswith("5.0"):
        with shell.pushd(llvm.get_project_directory(args, key)):
            shell.call([str(toolchain.git), 'checkout', 'release_50'])

    return


def get_llvm_dependency_release(args, key, project_id, url_format, use_cmd_tar):
    version = args.llvm_version

    # Set the full path to the destination file.
    local_file = os.path.join(llvm.get_temp_directory(key),
                              project_id + '.tar.xz')

    # Delete the old directory.
    shell.rmtree(llvm.get_project_directory(args, key))
    shell.rmtree(llvm.get_temp_directory(key))

    # Make a new directory.
    shell.makedirs(llvm.get_project_directory(args, key))
    shell.makedirs(llvm.get_temp_directory(key))

    # Create the correct URL for downloading the source code.
    url = url_format.format(protocol='http', version=version, id=project_id)

    # Form the HTML GET call to stream the archive.
    request = requests.get(url=url, stream=True)

    # Stream the file to the final destination.
    with open(local_file, 'wb') as f:
        for chunk in request.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)

    print('Finished streaming from ' + url + ' to ' + str(local_file))

    if 2 == sys.version_info.major:
        if use_cmd_tar:
            # TODO Use different command for Windows.
            with shell.pushd(llvm.get_temp_directory(key)):
                shell.call(['tar', '-xf', project_id + '.tar.xz'])
        else:
            print('Extracting the downloaded file is not allowed.')
            return
    else:
        with tarfile.open(local_file) as f:
            f.extractall(llvm.get_temp_directory(key))

    # Delete the archive as it is extracted.
    shell.rm(local_file)

    # Set the original subdirectory name.
    subdir_name = '{}-{}.src'.format(project_id, version)

    print('The name of the LLVM subdirectory is ' + subdir_name)

    if 'libc++' == key:
        shell.rm(
            os.path.join(llvm.get_temp_directory(key), subdir_name, 'test',
                         'std', 'experimental', 'filesystem', 'Inputs',
                         'static_test_env', 'bad_symlink'))

    # Manually move the source files to the folder root.
    move_llvm_files(args=args, key=key, directory=subdir_name)


def get_llvm_dependency(args, key, project_id, url_format, git_url_format, project_git, use_cmd_tar, toolchain):
    version = args.llvm_version

    if version.startswith("6.0") or version.startswith("5.0"):
        get_llvm_dependency_git(args=args, key=key, git_url_format=git_url_format, project_git=project_git, toolchain=toolchain)
    else:
        get_llvm_dependency_release(args=args, key=key, project_id=project_id, url_format=url_format, use_cmd_tar=use_cmd_tar)


def get_gcc(args, gcc_node, url_format, use_cmd_tar):
    version = args.gcc_version

    # Set the full path to the destination file.
    local_file = os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp', 'gcc.tar.xz')

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp'))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp'))

    # Create the correct URL for downloading the source code.
    url = url_format.format(protocol='http',
                            mirror=args.gcc_mirror,
                            version=version,
                            extension='xz')

    # Form the HTML GET call to stream the archive.
    request = requests.get(url=url, stream=True)

    # Stream the file to the final destination.
    with open(local_file, 'wb') as f:
        for chunk in request.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)

    print('Finished streaming from ' + url + ' to ' + str(local_file))

    if sys.version_info.major == 2:
        if use_cmd_tar:
            # TODO Use different command for Windows.
            with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp')):
                shell.call(['tar', '-xf', 'gcc.tar.xz'])
        else:
            print('Extracting the downloaded file is not allowed.')
            return
    else:
        with tarfile.open(local_file) as f:
            f.extractall(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', 'temp'))

    # Delete the archive as it is extracted.
    shell.rm(local_file)

    # Set the original subdirectory name.
    subdir_name = 'gcc-{}'.format(version)

    print('The name of the GCC subdirectory is ' + subdir_name)

    # Manually move the source files to the folder root.
    move_gcc_files(args=args, directory=subdir_name)

    # Set permissions to the custom wget.
    if platform.system() == 'Darwin':
        shell.call(['chmod', '+x', os.path.join(ANTHEM_SOURCE_ROOT,
                                                'unsung-anthem',
                                                'utils',
                                                'wget')])

        # Download the prerequisites.
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', version)):
            env = {'PATH': '{}:{}'.format(os.environ['PATH'],
                                      os.path.join(ANTHEM_SOURCE_ROOT,
                                                   'unsung-anthem',
                                                   'utils'))}
            shell.call([str(os.path.join('contrib',
                                         'download_prerequisites'))],
                       env=env)

    else:
        # Download the prerequisites.
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, 'gcc', version)):
            shell.call([str(os.path.join('contrib',
                                         'download_prerequisites'))])


def get_cmake(args, key, version, url_format, protocol, curl):
    # Set the full path to the destination file.
    if 'Windows' == platform.system():
        local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp', key + '.zip')
    else:
        local_file = os.path.join(ANTHEM_SOURCE_ROOT,
                                  key,
                                  'temp',
                                  key + '.tar.gz')

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, args.cmake_version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, args.cmake_version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

    # Set the full version of the CMake release.
    full_version = args.cmake_version

    # Set the version containing the major and minor version numbers of the
    # CMake release.
    major_minor_version = '{}.{}'.format(version['major'], version['minor'])

    # Set the platform name for the CMake download.
    if 'Windows' == platform.system():
        cmake_platform = 'win32-x86'
    elif 'Linux' == platform.system():
        # Starting at CMake 3.1.0 'Linux-x86_64' variant is available, before
        # that the only option is 'Linux-i386'.
        if args.cmake_major_version < 3:
            cmake_platform = 'Linux-i386'
        else:
            if args.cmake_minor_version < 1:
                cmake_platform = 'Linux-i386'
            else:
                cmake_platform = 'Linux-x86_64'
    elif 'Darwin' == platform.system():
        # Starting at CMake 3.1.1 'Darwin-x86_64' variant is available, before
        # that the only option is 'Darwin-universal'.
        if args.cmake_major_version < 3:
            cmake_platform = 'Darwin-universal'
        else:
            if args.cmake_minor_version <= 1:
                if args.cmake_patch_version < 1:
                    cmake_platform = 'Darwin-universal'
                else:
                    cmake_platform = 'Darwin-x86_64'
            else:
                cmake_platform = 'Darwin-x86_64'
    else:
        diagnostics.note('CMake will not be downloaded as the platform is not '
                         'supported.')
        return

    # Set the file extension according to the system.
    if 'Windows' == platform.system():
        archive_extension = 'zip'
    else:
        archive_extension = 'tar.gz'

    # Create the correct URL for downloading the source code.
    url = url_format.format(protocol=protocol,
                            major_minor=major_minor_version,
                            version=full_version,
                            platform=cmake_platform,
                            extension=archive_extension)

    # Form the HTML GET call to stream the archive.
    if curl:
        shell.call(['curl', '-o', local_file, '--create-dirs', url])
    else:
        request = requests.get(url=url, stream=True)

        # Stream the file to the final destination.
        with open(local_file, 'wb') as f:
            for chunk in request.iter_content(chunk_size=1024):
                if chunk:
                    f.write(chunk)

    print('Finished streaming from ' + url + ' to ' + str(local_file))

    if 'Windows' == platform.system():
        # Extract the archive.
        with contextlib.closing(zipfile.ZipFile(local_file, 'r')) as z:
            z.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))
    else:
        # Open the archive.
        tar = tarfile.open(local_file, "r:gz")

        # Extract the archive to the correct subdirectory.
        tar.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

        # Close the open file.
        tar.close()

    # Delete the archive as it is extracted.
    shell.rm(local_file)

    # Set the original subdirectory name.
    subdir_name = 'cmake-{}-{}'.format(full_version, cmake_platform)

    diagnostics.note('The name of the CMake subdirectory is ' + subdir_name)

    # Manually move the source files to the folder root.
    move_cmake_files(args=args, key=key, directory=subdir_name)


def get_sdl(args, asset, curl):
    key = 'sdl'
    version = args.sdl_version

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

    # Set the file extension according to the system.
    if platform.system() == 'Windows':
        archive_extension = 'zip'
    else:
        archive_extension = 'tar.gz'

    # Set the URL according to the system.
    if platform.system() == 'Windows':
        url_format = asset['windows_format']

        url = url_format.format(protocol='https',
                                version=version,
                                type='VC',
                                extension=archive_extension)
    else:
        url_format = asset['format']

        url = url_format.format(protocol='https',
                                version=version,
                                extension=archive_extension)

    local_file = os.path.join(ANTHEM_SOURCE_ROOT, key,
                              'temp',
                              key + '.' + archive_extension)

    # Form the HTML GET call to stream the archive.
    if curl:
        shell.call(['curl', '-o', local_file, '--create-dirs', url])
    else:
        request = requests.get(url=url, stream=True)

        # Stream the file to the final destination.
        with open(local_file, 'wb') as f:
            for chunk in request.iter_content(chunk_size=1024):
                if chunk:
                    f.write(chunk)

    diagnostics.note('Finished streaming from '
                     + url
                     + ' to '
                     + str(local_file))

    if 'Windows' == platform.system():
        # Extract the archive.
        with contextlib.closing(zipfile.ZipFile(local_file, 'r')) as z:
            z.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))
    else:
        # Open the archive.
        tar = tarfile.open(local_file, "r:gz")

        # Extract the archive to the correct subdirectory.
        tar.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key, 'temp'))

        # Close the open file.
        tar.close()

    # Delete the archive as it is extracted.
    shell.rm(local_file)

    # Set the original subdirectory name.
    subdir_name = 'SDL2-{}'.format(version)

    diagnostics.note('The name of the SDL subdirectory is ' + subdir_name)

    # Manually move the source files to the folder root.
    move_sdl_files(args=args, key=key, directory=subdir_name)


def update(args, toolchain):
    freeze_support()

    with open(args.build_config) as f:
        config = json.load(f)

    # A dictionary that will contain the version for each dependency.
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as f:
            versions = json.load(f)
    else:
        versions = {}

    dependencies = config['dependencies']

    protocol = 'https' if not args.ci else 'https'

    diagnostics.note('Using {} protocol to make the HTTP '
                     'calls'.format(protocol.upper()))

    for key in dependencies.keys():

        # Check if the dependency should be skipped.
        if key in args.skip_repository_list:
            diagnostics.note('' + key + ' is on the list of repositories to '
                                        'be skipped')
            continue

        # Set a shortcut to the dependency data.
        dependency = dependencies[key]

        # Check if the dependency should be re-downloaded.
        if key in versions and not args.clean:
            if versions[key] == args.version_info[key] \
                    and versions[key] != "git":
                print('' + key + ' should not be re-downloaded, skipping.')
                continue

        if dependency['github']:
            get_github_dependency(args, toolchain, key, dependency, protocol)
        else:
            if key == 'llvm':
                # Set the URL format of the LLVM downloads.
                url_format = dependency['asset']['format']

                # Set the URL format of the LLVM git repositories.
                git_url_format = dependency['git_format']

                for project in dependency['projects'].keys():
                    # Check if the specific LLVM project should be skipped.
                    if "{}-{}".format(key,
                                      project) in args.skip_repository_list:
                        diagnostics.note('{}-{} is on the list of repositories '
                                         'to be skipped'.format(key, project))
                        continue

                    # Set the project.
                    project_json = dependency['projects'][project]

                    # Set the project git.
                    project_git = project_json['git']

                    get_llvm_dependency(args=args,
                                        key=project,
                                        project_id=project_json['id'],
                                        url_format=url_format,
                                        git_url_format=git_url_format,
                                        project_git=project_git,
                                        use_cmd_tar=(
                                            not args.disable_manual_tar),
                                        toolchain=toolchain)

                # Finally, delete the master temp directory of LLVM.
                shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'llvm', 'temp'))
            elif key == 'gcc':
                # Set the URL format of the GCC downloads.
                url_format = dependency['asset']['format']

                get_gcc(args=args,
                        gcc_node=dependency,
                        url_format=url_format,
                        use_cmd_tar=not args.disable_manual_tar)
            elif key == 'cmake':
                get_cmake(args=args,
                          key=key,
                          version=args.version_info['cmake_info'],
                          url_format=dependency['asset']['format'],
                          protocol=protocol,
                          curl=args.ci)
            elif key == 'sdl':
                get_sdl(args=args, asset=dependency['asset'], curl=args.ci)

        # Add the version of the dependency to the dictionary.
        if is_commit(args.version_info[key]) \
                or is_branch(args.version_info[key]):
            versions[key] = parse_git_version(args.version_info[key])
        else:
            versions[key] = args.version_info[key]

    # Write the versions to the file.
    dump_version_info(versions)

    return 0
