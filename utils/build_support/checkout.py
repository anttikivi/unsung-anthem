#===-------------------------- checkout.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for setting up the checkout.
"""


import json
import os

from . import config, diagnostics

from .variables import ANTHEM_SOURCE_ROOT

VERSIONS_FILE = os.path.join(ANTHEM_SOURCE_ROOT, "versions")


def get_product(build_data, key, versions):
    """
    """
    product = build_data.products[key]
    if product.github_data:
        diagnostics.debug(
            "{} is a GitHub project and it will be downloaded from "
            "GitHub".format(product.repr))
    else:
        diagnostics.debug(
            "GitHub data is not found from {} and, thus, a custom function "
            "is used to download it".format(product.repr))


def update(build_data):
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as json_file:
            versions = json.load(json_file)
    else:
        versions = {}

    protocol = config.PROTOCOL

    diagnostics.debug(
        "Using {} protocol to make the HTTP calls".format(protocol.upper()))

    for key in build_data.products.keys():
        product = build_data.products[key]
        name = product.repr
        diagnostics.debug(
            "Beginning to process the checkout update of {}".format(name))
        if key in build_data.args.skip_repository_list:
            diagnostics.note(
                "{} is on the list of repositories to be skipped".format(
                    name))
            continue
        if key == "anthem":
            diagnostics.debug("{} is not downloaded in checkout".format(name))
            continue
        if not build_data.args.clean:
            if "checkout_check" in product \
                    and product.checkout_check is not None:
                if product.checkout_check(
                        build_data=build_data, versions=versions):
                    continue
            else:
                if key in versions and product.version == versions[key] \
                        and versions[key] != "git":
                    diagnostics.note(
                        "{} should not be re-downloaded, skipping".format(
                            name))
                    continue

        get_product(build_data=build_data, key=key, versions=versions)

        diagnostics.debug_ok(
            "Checkout update of {} is complete".format(name))
