#===--------------------------- github.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for GitHub checkout.
"""


import os
import platform

from build_utils import diagnostics, shell

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT

from . import github_asset, github_tag


def simple_asset(key):
    """
    Download an asset from GitHub.

    key -- the name of the product.
    """
    product = data.build.products[key]
    asset = data.build.products[key].github_data.asset
    version = product.version
    if asset.source:
        diagnostics.trace("Entering the download of a source asset:")
        diagnostics.trace_head(product.repr)
        github_tag.download(key=key)
        if platform.system() != "Windows":
            shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
            shell.copytree(
                os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", key),
                os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    else:
        diagnostics.trace("Entering the download of an asset:")
        diagnostics.trace_head(asset.file)
        github_asset.download(key=key, asset_name=asset.file)
        shell.copy(
            os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", asset.file),
            os.path.join(ANTHEM_SOURCE_ROOT, key, version, asset.file)
        )


def platform_specific_asset(key):
    """
    Download a platform-specific asset from GitHub.

    key -- the name of the product.
    """
    asset = data.build.products[key].github_data.asset
    version = data.build.products[key].version
    if platform.system() in asset.platform_files.keys() \
            and asset.platform_files[platform.system()] is not None:
        diagnostics.trace(
            "Entering the download of a platform-specific asset:"
        )
        asset_file = asset.platform_files[platform.system()]
    elif asset.fallback:
        diagnostics.trace("Entering the download of a fallback asset:")
        asset_file = asset.fallback_file
    else:
        # TODO
        diagnostics.fatal("TODO")
        asset_file = None
    diagnostics.trace_head(asset_file)
    github_asset.download(key=key, asset_name=asset_file)
    dest_file = asset.file
    shell.tar(
        path=os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", dest_file),
        dest=os.path.join(ANTHEM_SOURCE_ROOT, key, version))


def get_dependency(key):
    """
    Download an asset from GitHub.

    key -- the name of the product.
    """
    product = data.build.products[key]
    version = product.version

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))

    asset = product.github_data.asset

    if asset.platform_specific:
        platform_specific_asset(key)
    else:
        simple_asset(key)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
