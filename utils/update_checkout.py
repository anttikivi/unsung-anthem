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
import zipfile

from multiprocessing import freeze_support

import sys

from anthem_build_support.anthem_build_support import (github, shell)
from anthem_build_support.anthem_build_support.variables import \
    ANTHEM_SOURCE_ROOT

SCRIPT_FILE = os.path.abspath(__file__)
SCRIPT_DIR = os.path.dirname(SCRIPT_FILE)

VERSIONS_FILE = os.path.join(ANTHEM_SOURCE_ROOT, 'versions')


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

    parser.add_argument("--scheme",
                        help='Use branches from the specified branch-scheme. '
                             'A "branch-scheme" is a list of (repo, branch) '
                             'pairs.',
                        metavar='BRANCH-SCHEME',
                        dest='scheme')

    parser.add_argument('--clean',
                        help='Force to re-download every dependency.',
                        action='store_true')

    parser.add_argument("--config",
                        default=os.path.join(SCRIPT_DIR,
                                             "update-checkout-config.json"),
                        help="Configuration file to use")

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

        # Set a shortcut to the dependency data.
        dependency = dependencies[key]

        # Set a shortcut to the asset data.
        asset = dependency['asset']

        # Check if the dependency should be re-downloaded.
        if os.path.isfile(VERSIONS_FILE) and\
                (versions[key] == dependency['version']) and not args.clean:
            print('' + key + ' should not be re-downloaded, skipping.')
            continue

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
                                                               asset['id']))
            else:
                if asset['fallback']:
                    github.download_asset(owner=dependency['owner'],
                                          repository=dependency['id'],
                                          release_name=dependency['version'],
                                          asset_name=asset['id'],
                                          destination=os.path.join(key,
                                                                   asset['id']))
                else:
                    print('Not supported')  # TODO
        else:
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name=dependency['version'],
                                  asset_name=asset['id'],
                                  destination=os.path.join(key, asset['id']))

        # Set the asset file for the processing of the file.
        asset_file = os.path.join(ANTHEM_SOURCE_ROOT, key, asset['id'])

        # Check if the downloaded asset is a zip archive.
        if '.zip' in asset_file:
            print('The downloaded asset is a zip archive. Extracting now.')

            # Use Python to extract the archive.
            with contextlib.closing(zipfile.ZipFile(asset_file, 'r')) as z:
                z.extractall(os.path.join(ANTHEM_SOURCE_ROOT, key))

            # Delete the archive as it is extracted.
            shell.rm(asset_file)

        # Do the manual tasks if this dependency requires them.
        if 'glfw' == key:
            move_glfw_files(config)

        # Add the version of the dependency to the dictionary.
        versions[key] = dependency['version']

    # Write the versions to the file.
    dump_version_info(versions)

    return 0


if __name__ == "__main__":
    sys.exit(main())
