# utils/update_checkout.py - Utility to update local checkouts ---*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

from __future__ import print_function

import argparse
import json
import os
import re
import sys
import traceback

from functools import reduce
from multiprocessing import freeze_support

from anthem_build_support.anthem_build_support import shell
from anthem_build_support.anthem_build_support.variables import \
    ANTHEM_SOURCE_ROOT

import requests

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

    if scheme is None:
        scheme = config['default-branch-scheme']

    skip_repo_list = args.skip_repository_list

    for k in config['repos'].keys():

        # Delete the old directory.
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, k))

        # Make a new directory.
        shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, k))

        print(config['branch-schemes'][scheme]['versions'][k])
        print(config['repos'][k]['remote']['id'])

        url = config['api-url'] + '/repos/' + config["repos"][k]['remote']['id'] + '/releases/v' + config['branch-schemes'][scheme]['versions'][k]
        headers = {"User-Agent": "anttikivi"}
        req = requests.get(url=url, headers=headers)

        print(url)
        print(req.text)

        url = req.json()['assets'][0]['url']
        # url = req.json()['tarball_url']
        headers = {"User-Agent": "venturesomestone",
                   "Accept": "application/octet-stream"}
        catch_assets_req = requests.get(url=url, headers=headers, stream=True)

        local_filename = os.path.join(ANTHEM_SOURCE_ROOT, k, 'k.tar.gz')

        with open(local_filename, 'wb') as f:
            for chunk in catch_assets_req.iter_content(chunk_size=1024):
                if chunk:  # filter out keep-alive new chunks
                    f.write(chunk)


if __name__ == "__main__":
    main()
