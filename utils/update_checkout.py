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

from anthem_build_support.anthem_build_support import (github, shell)
from anthem_build_support.anthem_build_support.variables import \
    ANTHEM_SOURCE_ROOT

SCRIPT_FILE = os.path.abspath(__file__)
SCRIPT_DIR = os.path.dirname(SCRIPT_FILE)


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
                        help='Clean unrelated files from each repository.',
                        action='store_true')

    parser.add_argument("--config",
                        default=os.path.join(SCRIPT_DIR,
                                             "update-checkout-config.json"),
                        help="Configuration file to use")

    args = parser.parse_args()

    scheme = args.scheme

    with open(args.config) as f:
        config = json.load(f)

    dependencies = config['dependencies']

    print(platform.system())

    for key in dependencies.keys():
        # Delete the old directory.
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key))

        # Make a new directory.
        shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key))

        # Set a shortcut to the dependency data.
        dependency = dependencies[key]

        # Set a shortcut to the asset data.
        asset = dependency['asset']

        # Check whether the asset has different version on different
        # platforms.
        if asset['multiplatform']:
            if platform.system() in asset.keys():
                github.download_asset(owner=dependency['owner'],
                                      repository=dependency['id'],
                                      release_name='v' + dependency['version'],
                                      asset_name=asset[platform.system()],
                                      destination=os.path.join(key,
                                                               asset['id']))
            else:
                print('Not supported')  # TODO
        else:
            github.download_asset(owner=dependency['owner'],
                                  repository=dependency['id'],
                                  release_name='v' + dependency['version'],
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


if __name__ == "__main__":
    main()
