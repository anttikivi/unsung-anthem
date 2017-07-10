# utils/update_checkout.py - Utility to update local checkouts ---*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

from __future__ import print_function

import argparse
import contextlib
import json
import os
import platform
import tarfile
import zipfile

from multiprocessing import freeze_support

import sys

import requests

from anthem_build_support.anthem_build_support import \
    (diagnostics, github, shell)
from anthem_build_support.anthem_build_support.variables import \
    ANTHEM_SOURCE_ROOT

SCRIPT_FILE = os.path.abspath(__file__)
SCRIPT_DIR = os.path.dirname(SCRIPT_FILE)

VERSIONS_FILE = os.path.join(ANTHEM_SOURCE_ROOT, 'versions')


def move_source_files(key, owner, repository, sha):
    # Delete the temporary folder in case it exists.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))

    # Move up the source files to temporary folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                key,
                                owner + '-' + repository + '-' + sha),
                   os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))

    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'),
                   os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))


def move_dependency_files(key, directory):
    # Delete the temporary folder in case it exists.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))

    # Move up the source files to temporary folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, key, directory),
                   os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))

    # Delete the old folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'),
                   os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))


def move_glfw_files(config):
    # Delete the temporary folder in case it exists.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))

    # Move up the GLFW files to temporary folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                'glfw',
                                'glfw-'
                                + config['dependencies']['glfw']['version']),
                   os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))

    # Delete the GLFW folder so the files in the temporary folder can be
    # copied.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'glfw'))

    # Copy the files from the temporary folder to the correct folder.
    shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'),
                   os.path.join(ANTHEM_SOURCE_ROOT, 'glfw'))

    # Delete the temporary folder.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))


def dump_version_info(versions):
    # Write the versions to a JSON file so next time the script can download
    # only the ones that are updated.
    with open(os.path.join(ANTHEM_SOURCE_ROOT, 'versions'), 'w') as outfile:
        json.dump(versions, outfile)


def get_github_dependency(args, config, key, dependency, versions):
    # Set a shortcut to the asset data.
    asset = dependency['asset']

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Check whether the asset has different version on different
    # platforms.
    if asset['multiplatform']:
        if platform.system() in asset.keys():
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name=dependency['version'],
                                  asset_name=asset[platform.system()],
                                  destination=os.path.join(key,
                                                           asset['id']),
                                  travis=args.travis)
        else:
            if asset['fallback']:
                github.download_asset(owner=dependency['owner'],
                                      repository=dependency['id'],
                                      release_name=dependency['version'],
                                      asset_name=asset['id'],
                                      destination=os.path.join(key,
                                                               asset['id']),
                                      travis=args.travis)
            else:
                print('Not supported')  # TODO
    else:
        if asset['source']:
            github.download_source(owner=dependency['owner'],
                                   repository=dependency['id'],
                                   release_name=dependency['version'],
                                   destination=os.path.join(key,
                                                            key
                                                            + '.tar.gz'),
                                   travis=args.travis)
        else:
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name=dependency['version'],
                                  asset_name=asset['id'],
                                  destination=os.path.join(key,
                                                           asset['id']),
                                  travis=args.travis)

    if asset['source']:
        # Set the asset file for the processing of the file to the
        # downloaded source tarball.
        asset_file = os.path.join(ANTHEM_SOURCE_ROOT, key, key + '.tar.gz')

        # Open the archive.
        tar = tarfile.open(asset_file, "r:gz")

        # Extract the archive to the correct subdirectory.
        tar.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key))

        # Close the open file.
        tar.close()

        # Delete the archive as it is extracted.
        shell.rm(asset_file)

        if 'docopt' == key:
            # Manually move the source file via the custom function for
            # docopt.
            move_dependency_files(key,
                                  os.listdir(
                                      os.path.join(ANTHEM_SOURCE_ROOT,
                                                   key))[0])
        else:
            # Get the short SHA of the tag for handling the downloaded
            # files.
            sha = github.get_release_short_sha(owner=dependency['owner'],
                                               repository=dependency['id'],
                                               release_name=
                                               dependency['version'],
                                               travis=args.travis)

            # Manually move the downloaded sources to the actual directory.
            move_source_files(key=key,
                              owner=dependency['owner'],
                              repository=dependency['id'],
                              sha=sha)
    else:
        # If the current dependency is Bazel, continue as it should not be
        # extracted.
        if not ('bazel' == key):
            # Set the asset file for the processing of the file.
            asset_file = os.path.join(ANTHEM_SOURCE_ROOT, key, asset['id'])

            # Check if the downloaded asset is a zip archive.
            if '.zip' in asset_file:
                print('The downloaded asset is a zip archive. Extracting '
                      'now.')

                # Use Python to extract the archive.
                with contextlib.closing(zipfile.ZipFile(asset_file, 'r')) as z:
                    z.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key))

                # Delete the archive as it is extracted.
                shell.rm(asset_file)

            # Do the manual tasks if this dependency requires them.
            if 'glfw' == key:
                move_glfw_files(config)


def get_llvm_dependency(key, id, version, url_format, use_cmd_tar):
    # Set the full path to the destination file.
    local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, id + '.tar.xz')

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Create the correct URL for downloading the source code.
    url = url_format % (version, id, version)

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
            with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key)):
                shell.call(['tar', '-xf', id + '.tar.xz'])
        else:
            print('Extracting the downloaded file is not allowed.')
            return
    else:
        with tarfile.open(local_file) as f:
            f.extractall(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Delete the archive as it is extracted.
    shell.rm(local_file)

    # Set the original subdirectory name.
    subdir_name = '%s-%s.src' % (id, version)

    print('The name of the LLVM subdirectory is ' + subdir_name)

    if 'libc++' == key:
        shell.rm(
            os.path.join(ANTHEM_SOURCE_ROOT, key, subdir_name, 'test', 'std',
                         'experimental', 'filesystem', 'Inputs',
                         'static_test_env', 'bad_symlink'))

    # Manually move the source files to the folder root.
    move_dependency_files(key=key, directory=subdir_name)


def get_cmake(key, version, url_format):
    # Set the full path to the destination file.
    if 'Windows' == platform.system():
        local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, key + '.zip')
    else:
        local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, key + '.tar.gz')

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Set the full version of the CMake release.
    full_version = '%s.%s.%s' \
                   % (version['major'], version['minor'], version['patch'])

    # Set the version containing the major and minor version numbers of the
    # CMake release.
    major_minor_version = '%s.%s' % (version['major'], version['minor'])

    # Set the platform name for the CMake download.
    if 'Windows' == platform.system():
        cmake_platform = 'win32-x86'
    elif 'Linux' == platform.system():
        cmake_platform = 'Linux-x86_64'
    elif 'Darwin' == platform.system():
        cmake_platform = 'Darwin-x86_64'
    else:
        print('CMake will not be downloaded as the platform is not supported.')
        return

    # Set the file extension according to the system.
    if 'Windows' == platform.system():
        archive_extension = '.zip'
    else:
        archive_extension = '.tar.gz'

    # Create the correct URL for downloading the source code.
    url = url_format % (
        major_minor_version, full_version, cmake_platform, archive_extension)

    # Form the HTML GET call to stream the archive.
    request = requests.get(url=url, stream=True)

    # Stream the file to the final destination.
    with open(local_file, 'wb') as f:
        for chunk in request.iter_content(chunk_size=1024):
            if chunk:
                f.write(chunk)

    print('Finished streaming from ' + url + ' to ' + str(local_file))

    if 'Windows' == platform.system():
        print('TODO')
    else:
        # Open the archive.
        tar = tarfile.open(local_file, "r:gz")

        # Extract the archive to the correct subdirectory.
        tar.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key))

        # Close the open file.
        tar.close()

    # Delete the archive as it is extracted.
    shell.rm(local_file)

    # Set the original subdirectory name.
    subdir_name = 'cmake-%s-%s' % (full_version, cmake_platform)

    print('The name of the CMake subdirectory is ' + subdir_name)

    # Manually move the source files to the folder root.
    move_dependency_files(key=key, directory=subdir_name)


def main():
    freeze_support()
    parser = argparse.ArgumentParser(formatter_class= \
                                         argparse.RawDescriptionHelpFormatter,
                                     description="""repositories.
                                     
By default, updates your checkouts of Unsung Anthem.""")

    parser.add_argument("--skip-repository",
                        metavar="DIRECTORY",
                        default=[],
                        help="Skip the specified repository",
                        dest='skip_repository_list',
                        action="append")

    parser.add_argument('--clean',
                        help='Force to re-download every dependency.',
                        action='store_true')

    parser.add_argument("--config",
                        default=os.path.join(SCRIPT_DIR,
                                             "update-checkout-config.json"),
                        help="Configuration file to use")

    parser.add_argument('--disable-manual-tar',
                        help='Set in Travis for correct handling of the '
                             'dependency downloading.',
                        action='store_true')

    parser.add_argument('--travis',
                        help='TODO',
                        action='store_true')

    args = parser.parse_args()

    with open(args.config) as f:
        config = json.load(f)

    # A dictionary that will contain the version for each dependency.
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as f:
            versions = json.load(f)
    else:
        versions = {}

    dependencies = config['dependencies']

    for key in dependencies.keys():

        # Check if the dependency should be skipped.
        if key in args.skip_repository_list:
            diagnostics.note('' + key + ' is on the list of repositories to '
                                        'be skipped')
            continue

        # Set a shortcut to the dependency data.
        dependency = dependencies[key]

        # Check if the dependency should not be downloaded on Travis CI.
        if not dependency['travis'] and args.travis:
            diagnostics.note('' + key + ' should not be downloaded on Travis')
            continue

        # Check if the dependency should be re-downloaded.
        if os.path.isfile(VERSIONS_FILE) and key in versions and not args.clean:
            if 'cmake' == key:
                full_version = '%s.%s.%s' % (
                    dependency['version']['major'], dependency['version']['minor'],
                    dependency['version']['patch'])
                if versions[key] == full_version:
                    print('' + key + ' should not be re-downloaded, skipping.')
                    continue
            else:
                if versions[key] == dependency['version']:
                    print('' + key + ' should not be re-downloaded, skipping.')
                    continue

        if dependency['github']:
            get_github_dependency(args, config, key, dependency, versions)
        else:
            if 'llvm' == key:
                # Set the URL format of the LLVM downloads.
                url_format = dependency['asset']['format']

                for project in dependency['projects'].keys():
                    # Set the project.
                    project_json = dependency['projects'][project]

                    get_llvm_dependency(key=project,
                                        id=project_json['id'],
                                        version=dependency['version'],
                                        url_format=url_format,
                                        use_cmd_tar=(
                                            not args.disable_manual_tar))
            elif 'cmake' == key:
                get_cmake(key=key,
                          version=dependency['version'],
                          url_format=dependency['asset']['format'])

        # Add the version of the dependency to the dictionary.
        if 'cmake' == key:
            version_json = dependency['version']
            versions[key] = '%s.%s.%s' % (
            version_json['major'], version_json['minor'], version_json['patch'])
        else:
            versions[key] = dependency['version']

    # Write the versions to the file.
    dump_version_info(versions)

    return 0


if __name__ == "__main__":
    sys.exit(main())
