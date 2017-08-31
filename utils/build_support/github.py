#===--------------------------- github.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for using the GitHub API.
"""


import json
import os

import requests

from . import config, diagnostics

from .variables import ANTHEM_SOURCE_ROOT, SCRIPT_DIR


def stream_asset(build_data, key, url):
    """
    """
    product = build_data.products[key]
    github_data = product.github_data
    asset = github_data.asset
    destination = os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", asset.file)

    diagnostics.debug("Streaming an asset from {}".format(url))

    responce = requests.get(
        url=url,
        headers={
            "User-Agent": "venturesomestone",
            "Accept": "application/json"},
        stream=True)

    with open(destination, "wb") as destination_file:
        for chunk in responce.iter_content(chunk_size=1024):
            if chunk:
                destination_file.write(chunk)

    diagnostics.debug_ok(
        "Finished streaming an asset to {}".format(destination))


def download_asset(build_data, key, asset_name):
    """
    """
    product = build_data.products[key]
    github_data = product.github_data
    query = None

    with open(os.path.join(SCRIPT_DIR, "github_asset_query")) as query_file:
        raw_query = str(query_file.read())

    raw_query = raw_query.replace("{REPOSITORY_OWNER}", github_data.owner)
    raw_query = raw_query.replace("{REPOSITORY_NAME}", github_data.name)
    raw_query = raw_query.replace("{ASSET_NAME}", asset_name)

    query = json.dumps({"query": raw_query})

    diagnostics.trace("Calling the following GraphQL query:")
    diagnostics.trace(query)

    responce = requests.post(
        url=config.GITHUB_API_ENDPOINT,
        data=query,
        headers={
            "User-Agent": "venturesomestone",
            "Accept": "application/json",
            "Authorization": "bearer {}".format(build_data.github_token)})

    responce_json_data = responce.json()["data"]

    release_edges = responce_json_data["repository"]["releases"]["edges"]

    for edge in release_edges:
        node = edge["node"]
        if node["name"] == "":
            continue
        if github_data.version_prefix:
            github_version = "{}{}".format(
                github_data.version_prefix, product.version)
        else:
            github_version = product.version
        if node["name"] == github_version:
            diagnostics.debug(
                "Found the release {} ({}) of {}".format(
                    product.version, github_version, product.repr))
            release_asset_edges = node["releaseAssets"]["edges"]
            for asset_edge in release_asset_edges:
                asset_node = asset_edge["node"]
                stream_asset(
                    build_data=build_data, key=key, url=asset_node["url"])
