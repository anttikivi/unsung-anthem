#===------------------------ github_asset.py -----------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
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

from script_support.variables import ANTHEM_SOURCE_ROOT, SCRIPT_DIR

from . import github_v4_util


ASSET_QUERY_GRAPHQL = "github_asset.graphql"


def stream_asset(key, url):
    """
    Stream a single asset from GitHub.

    key -- the name of the product.
    url -- the URL from which the file is streamed.
    """
    product = data.build.products[key]
    github_data = product.github_data
    asset = github_data.asset
    destination = os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", asset.file)

    http_stream.stream(url=url, destination=destination, headers={
            "User-Agent": "venturesomestone",
            "Accept": "application/octet-stream"
    })


def download_v4(key, asset_name):
    """
    Download an asset from GitHub using the new GraphQL API.

    key -- the name of the product.
    asset_name -- the name of the asset.
    """
    product = data.build.products[key]
    github_data = product.github_data

    release_asset_edges = github_v4_util.find_release_node(
        key,
        github_v4_util.call_query(
            ASSET_QUERY_GRAPHQL,
            {
                "{REPOSITORY_OWNER}": github_data.owner,
                "{REPOSITORY_NAME}": github_data.name,
                "{ASSET_NAME}": asset_name
            }))["releaseAssets"]["edges"]

    for asset_edge in release_asset_edges:
        asset_node = asset_edge["node"]
        stream_asset(key=key, url=asset_node["url"])


def download(key, asset_name):
    """
    Download an asset from GitHub.

    key -- the name of the product.
    asset_name -- the name of the asset.
    """
    if data.build.github_token:
        download_v4(key=key, asset_name=asset_name)
    else:
        # TODO
        diagnostics.fatal("TODO")
