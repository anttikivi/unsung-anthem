#===--------------------------- github.py --------------------*- python -*-===#
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
import platform

import requests

from . import config, diagnostics, shell

from .httpstream import stream_file

from .variables import ANTHEM_SOURCE_ROOT, SCRIPT_DIR


def stream_asset(build_data, key, url):
    """
    Stream a single asset from GitHub.

    build_data -- the build data.
    key -- the name of the product.
    url -- the URL from which the file is streamed.
    """
    product = build_data.products[key]
    github_data = product.github_data
    asset = github_data.asset
    destination = os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", asset.file)

    stream_file(
        build_data=build_data, url=url, destination=destination, headers={
            "User-Agent": "venturesomestone",
            "Accept": "application/octet-stream"
        }
    )


def download_asset(build_data, key, asset_name):
    """
    Download an asset from GitHub.

    build_data -- the build data.
    key -- the name of the product.
    asset_name -- the name of the asset.
    """
    product = build_data.products[key]
    github_data = product.github_data
    query = None

    with open(os.path.join(SCRIPT_DIR, "github_asset.graphql")) as query_file:
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


def checkout_tag_windows(build_data, key, tag_ref_name):
    """
    Checkout a tag.

    build_data -- the build data.
    key -- the name of the product.
    tag_ref_name -- the name of the tag.
    """
    with shell.pushd(os.path.join(
            ANTHEM_SOURCE_ROOT, key, build_data.products[key].version)):
        shell.call([
            build_data.toolchain.git, "checkout",
            "tags/{}".format(tag_ref_name), "-b",
            "{}_branch".format(tag_ref_name)])


def checkout_tag(build_data, key, tag_ref_name):
    """
    Checkout a tag.

    build_data -- the build data.
    key -- the name of the product.
    tag_ref_name -- the name of the tag.
    """
    with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", key)):
        shell.call([
            build_data.toolchain.git, "checkout",
            "tags/{}".format(tag_ref_name), "-b",
            "{}_branch".format(tag_ref_name)])


def download_tag(build_data, key):
    """
    Download a tag from GitHub.

    build_data -- the build data.
    key -- the name of the product.
    """
    product = build_data.products[key]
    github_data = product.github_data
    query = None

    with open(os.path.join(SCRIPT_DIR, "github_tag.graphql")) as query_file:
        raw_query = str(query_file.read())

    raw_query = raw_query.replace("{REPOSITORY_OWNER}", github_data.owner)
    raw_query = raw_query.replace("{REPOSITORY_NAME}", github_data.name)

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

    if platform.system() == "Windows":
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key)):
            shell.call([
                build_data.toolchain.git, "clone",
                "{}.git".format(responce_json_data["repository"]["url"]),
                product.version])
    else:
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp")):
            shell.call([
                build_data.toolchain.git, "clone",
                "{}.git".format(responce_json_data["repository"]["url"])])

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
            tag_ref_name = node["tag"]["name"]
            if platform.system() == "Windows":
                checkout_tag_windows(
                    build_data=build_data, key=key, tag_ref_name=tag_ref_name)
            else:
                checkout_tag(
                    build_data=build_data, key=key, tag_ref_name=tag_ref_name)
            return
