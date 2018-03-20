#===------------------------------ github.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for GitHub checkout."""


import os
import platform

from build_utils import diagnostics, shell, workspace

from . import github_asset, github_tag


def simple_asset(product):
    """Download an asset from GitHub."""
    asset = product.github_data.asset
    if asset.source:
        diagnostics.trace("Entering the download of a source asset:")
        diagnostics.trace_head(product.repr)
        github_tag.download(product=product)
        if platform.system() != "Windows":
            source_dir = workspace.source_dir(product=product)
            version_dir = os.path.dirname(source_dir)
            shell.rmtree(source_dir)
            shell.rmtree(version_dir)
            shell.copytree(
                os.path.join(workspace.temp_dir(product=product), product.key),
                workspace.source_dir(product=product))
    else:
        diagnostics.trace("Entering the download of an asset:")
        diagnostics.trace_head(asset.file)
        github_asset.download(product=product, asset_name=asset.file)
        shell.copy(
            os.path.join(workspace.temp_dir(product=product), asset.file),
            os.path.join(workspace.source_dir(product=product), asset.file))


def platform_specific_asset(product):
    """Download a platform-specific asset from GitHub."""
    asset = product.github_data.asset
    if platform.system() in asset.platform_files.keys() \
            and asset.platform_files[platform.system()] is not None:
        diagnostics.trace(
            "Entering the download of a platform-specific asset:")
        asset_file = asset.platform_files[platform.system()]
    elif asset.fallback:
        diagnostics.trace("Entering the download of a fallback asset:")
        asset_file = asset.fallback_file
    else:
        # TODO
        diagnostics.fatal("TODO")
        asset_file = None
    diagnostics.trace_head(asset_file)
    github_asset.download(product=product, asset_name=asset_file)
    dest_file = asset.file
    shell.tar(
        path=os.path.join(workspace.temp_dir(product=product), dest_file),
        dest=workspace.source_dir(product=product))


def get_dependency(product):
    """Download an asset from GitHub."""
    shell.rmtree(workspace.source_dir(product=product))
    shell.rmtree(workspace.temp_dir(product=product))
    shell.makedirs(workspace.source_dir(product=product))
    shell.makedirs(workspace.temp_dir(product=product))
    asset = product.github_data.asset
    if asset.platform_specific:
        diagnostics.trace("The asset of {} is platform-specific".format(
            product.repr))
        platform_specific_asset(product)
    else:
        diagnostics.trace("The asset of {} is simple".format(product.repr))
        simple_asset(product)
    shell.rmtree(workspace.temp_dir(product=product))
