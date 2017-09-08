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
import platform

from . import config, diagnostics, github, modules, shell

from .variables import ANTHEM_SOURCE_ROOT, VERSIONS_FILE


def simple_asset(build_data, key):
    """
    """
    product = build_data.products[key]
    asset = build_data.products[key].github_data.asset
    version = product.version
    if asset.source:
        diagnostics.trace("Entering the download of a source asset:")
        diagnostics.trace_head(product.repr)
        github.download_tag(build_data=build_data, key=key)
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
        shell.copytree(
            os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", key),
            os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    else:
        diagnostics.trace("Entering the download of an asset:")
        diagnostics.trace_head(asset.file)
        github.download_asset(
            build_data=build_data,
            key=key,
            asset_name=asset.file)
        shell.copy(
            os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", asset.file),
            os.path.join(ANTHEM_SOURCE_ROOT, key, version, asset.file))


def platform_specific_asset(build_data, key):
    """
    """
    asset = build_data.products[key].github_data.asset
    version = build_data.products[key].version
    if platform.system() in asset.platform_files.keys() \
            and asset.platform_files[platform.system()] is not None:
        diagnostics.trace(
            "Entering the download of a platform-specific asset:")
        asset_file = asset.platform_files[platform.system()]
    elif asset.fallback:
        diagnostics.trace(
            "Entering the download of a fallback asset:")
        asset_file = asset.fallback_file
    else:
        # TODO
        diagnostics.fatal("TODO")
        asset_file = None
    diagnostics.trace_head(asset_file)
    github.download_asset(
        build_data=build_data, key=key, asset_name=asset_file)
    dest_file = asset.file
    shell.tar(
        path=os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", dest_file),
        dest=os.path.join(ANTHEM_SOURCE_ROOT, key, version))


def github_dependency(build_data, key):
    """
    """
    product = build_data.products[key]
    version = product.version

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))

    asset = product.github_data.asset

    if asset.platform_specific:
        platform_specific_asset(build_data=build_data, key=key)
    else:
        simple_asset(build_data=build_data, key=key)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))


def get_product(build_data, key, versions):
    """
    """
    product = build_data.products[key]
    if product.github_data:
        diagnostics.debug(
            "{} is a GitHub project and it will be downloaded from "
            "GitHub".format(product.repr))
        github_dependency(build_data=build_data, key=key)
    else:
        diagnostics.debug(
            "GitHub data is not found from {} and, thus, a custom function "
            "is used to download it".format(product.repr))
        modules.product_call(product, "get_dependency", build_data=build_data)

    if "inject_version_info" in product \
            and product.inject_version_info is not None:
        product.inject_version_info(build_data=build_data, versions=versions)
    else:
        version = product.version
        versions[key] = version


def update(build_data):
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as json_file:
            versions = json.load(json_file)
    else:
        versions = {}

    protocol = config.PROTOCOL

    diagnostics.debug(
        "Using {} protocol to make the HTTP calls".format(protocol.upper()))

    diagnostics.trace("The dependencies to be skipped are {}".format(
        str(build_data.args.skip_repository_list)))

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
            if "skip_checkout" in product \
                    and product.skip_checkout is not None:
                if product.skip_checkout(
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

        if "post_checkout" in product and product.post_checkout is not None:
            product.post_checkout(build_data=build_data)

        diagnostics.debug_ok(
            "Checkout update of {} is complete".format(name))

    with open(os.path.join(ANTHEM_SOURCE_ROOT, "versions"), "w") as outfile:
        json.dump(versions, outfile)

    diagnostics.debug_ok(
        "Wrote the dependecy version information to {}".format(
            os.path.join(ANTHEM_SOURCE_ROOT, "versions")))
