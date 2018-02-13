#===--------------------------- github_asset.py --------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for downloading an asset from
GitHub.
"""


import os

from build_utils import diagnostics, http_stream

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT

from . import github_v4_util


ASSET_QUERY_GRAPHQL = "github_asset.graphql"


def stream_asset(product, url):
    """Stream a single asset from GitHub."""
    key = product.key
    github_data = product.github_data
    asset = github_data.asset
    destination = os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", asset.file)
    http_stream.stream(url=url, destination=destination, headers={
        "User-Agent": "venturesomestone", "Accept": "application/octet-stream"
    })


def download_v4(product, asset_name):
    """Download an asset from GitHub using the new GraphQL API."""
    github_data = product.github_data
    release_asset_edges = github_v4_util.find_release_node(
        product, github_v4_util.call_query(ASSET_QUERY_GRAPHQL, {
            "{REPOSITORY_OWNER}": github_data.owner,
            "{REPOSITORY_NAME}": github_data.name, "{ASSET_NAME}": asset_name
        }), let_use_fallback=True)["releaseAssets"]["edges"]
    for asset_edge in release_asset_edges:
        asset_node = asset_edge["node"]
        stream_asset(product=product, url=asset_node["url"])


def download(product, asset_name):
    """Download an asset from GitHub."""
    if data.build.github_token:
        download_v4(product=product, asset_name=asset_name)
    else:
        # TODO
        diagnostics.fatal("TODO")
