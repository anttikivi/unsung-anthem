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

from . import (diagnostics, github, shell)
from variables import ANTHEM_SOURCE_ROOT

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
    if platform.system() == 'Windows':
        shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                    'glfw',
                                    'glfw-'
                                    + config['dependencies']['glfw']['version']
                                    + '.bin.WIN32'),
                       os.path.join(ANTHEM_SOURCE_ROOT, 'temp'))
    else:
        shell.copytree(os.path.join(ANTHEM_SOURCE_ROOT,
                                    'glfw',
                                    'glfw-'
                                    + config['dependencies']['glfw'][
                                        'version']),
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


def get_github_dependency(args, config, key, dependency, versions, protocol):
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
                                  ci=args.ci,
                                  protocol=protocol)
        else:
            if asset['fallback']:
                github.download_asset(owner=dependency['owner'],
                                      repository=dependency['id'],
                                      release_name=dependency['version'],
                                      asset_name=asset['id'],
                                      destination=os.path.join(key,
                                                               asset['id']),
                                      ci=args.ci,
                                      protocol=protocol)
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
                                   ci=args.ci,
                                   protocol=protocol)
        else:
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name=dependency['version'],
                                  asset_name=asset['id'],
                                  destination=os.path.join(key,
                                                           asset['id']),
                                  ci=args.ci,
                                  protocol=protocol)

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

        # Get the short SHA of the tag for handling the downloaded  files.
        sha = github.get_release_short_sha(owner=dependency['owner'],
                                           repository=dependency['id'],
                                           release_name=dependency['version'],
                                           ci=args.ci,
                                           protocol=protocol)

        # Manually move the downloaded sources to the actual directory.
        move_source_files(key=key,
                          owner=dependency['owner'],
                          repository=dependency['id'],
                          sha=sha)
    else:
        # Set the asset file for the processing of the file.
        asset_file = os.path.join(ANTHEM_SOURCE_ROOT, key, asset['id'])

        # Check if the downloaded asset is a zip archive.
        if '.zip' in asset_file:
            print('The downloaded asset is a zip archive. Extracting now.')

            # Use Python to extract the archive.
            with contextlib.closing(zipfile.ZipFile(asset_file, 'r')) as z:
                z.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key))

            # Delete the archive as it is extracted.
            shell.rm(asset_file)

        # Do the manual tasks if this dependency requires them.
        if 'glfw' == key:
            move_glfw_files(config)


def get_llvm_dependency(key, id, version, url_format, use_cmd_tar, protocol):
    # Set the full path to the destination file.
    local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, id + '.tar.xz')

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Create the correct URL for downloading the source code.
    url = url_format.format(protocol, version, id, version)

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
    subdir_name = '{}-{}.src'.format(id, version)

    print('The name of the LLVM subdirectory is ' + subdir_name)

    if 'libc++' == key:
        shell.rm(
            os.path.join(ANTHEM_SOURCE_ROOT, key, subdir_name, 'test', 'std',
                         'experimental', 'filesystem', 'Inputs',
                         'static_test_env', 'bad_symlink'))

    # Manually move the source files to the folder root.
    move_dependency_files(key=key, directory=subdir_name)


def get_cmake(key, version, url_format, protocol, curl):
    # Set the full path to the destination file.
    if 'Windows' == platform.system():
        filename = key + '.zip'
        local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, key + '.zip')
    else:
        filename = key + '.tar.gz'
        local_file = os.path.join(ANTHEM_SOURCE_ROOT, key, key + '.tar.gz')

    # Delete the old directory.
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Make a new directory.
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

    # Set the full version of the CMake release.
    full_version = '{}.{}.{}'.format(version['major'],
                                     version['minor'],
                                     version['patch'])

    # Set the version containing the major and minor version numbers of the
    # CMake release.
    major_minor_version = '{}.{}'.format(version['major'], version['minor'])

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
    url = url_format.format(
        protocol, major_minor_version, full_version, cmake_platform,
        archive_extension)

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
            z.extractall(path=os.path.join(ANTHEM_SOURCE_ROOT, key))
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
    subdir_name = 'cmake-{}-{}'.format(full_version, cmake_platform)

    print('The name of the CMake subdirectory is ' + subdir_name)

    # Manually move the source files to the folder root.
    move_dependency_files(key=key, directory=subdir_name)


def update(args):
    freeze_support()

    with open(args.checkout_config) as f:
        config = json.load(f)

    # A dictionary that will contain the version for each dependency.
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as f:
            versions = json.load(f)
    else:
        versions = {}

    dependencies = config['dependencies']

    protocol = 'https'  # if not args.travis else 'https'

    diagnostics.note('Using {} protocol to make the HTTP '
                     'calls'.format(protocol))

    for key in dependencies.keys():

        # Check if the dependency should be skipped.
        if key in args.skip_repository_list:
            diagnostics.note('' + key + ' is on the list of repositories to '
                                        'be skipped')
            continue

        # Set a shortcut to the dependency data.
        dependency = dependencies[key]

        # Check if the dependency should be re-downloaded.
        if os.path.isfile(VERSIONS_FILE) and key in versions and not args.clean:
            if 'cmake' == key:
                version_info = dependency['version']
                full_version = '{}.{}.{}'.format(version_info['major'],
                                                 version_info['minor'],
                                                 version_info['patch'])
            else:
                full_version = dependency['version']

            if versions[key] == full_version:
                print('' + key + ' should not be re-downloaded, skipping.')
                continue

        if dependency['github']:
            get_github_dependency(args, config, key, dependency, versions,
                                  protocol)
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
                                            not args.disable_manual_tar),
                                        protocol=protocol)
            elif 'cmake' == key:
                get_cmake(key=key,
                          version=dependency['version'],
                          url_format=dependency['asset']['format'],
                          protocol=protocol,
                          curl=args.ci)

        # Add the version of the dependency to the dictionary.
        if 'cmake' == key:
            version_json = dependency['version']
            full_version = '{}.{}.{}'.format(version_json['major'],
                                             version_json['minor'],
                                             version_json['patch'])
        else:
            full_version = dependency['version']

        versions[key] = full_version

    # Write the versions to the file.
    dump_version_info(versions)

    return 0
