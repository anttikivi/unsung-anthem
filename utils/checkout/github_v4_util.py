#===----------------------- github_v4_util.py ----------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for GitHub API v4.
"""


import json
import os

import requests

from build_utils import diagnostics

from script_support import config, data

from script_support.variables import SCRIPT_DIR


def get_github_version(key):
    """
    Concatenate the full version for GitHub.

    key -- the name of the product.
    """
    product = data.build.products[key]
    github_data = product.github_data

    if github_data.version_prefix:
        ret = "{}{}".format(
            github_data.version_prefix,
            product.version)
    else:
        ret = product.version

    return ret


def call_query(file_name, replacements=None):
    """
    Calls the given GraphQL query.

    raw_query -- the actual GraphQL query.
    replacements -- dictionary of values and keys which are replaced in the raw
    query before calling.
    """
    with open(os.path.join(SCRIPT_DIR, file_name)) as query_file:
        raw_query = str(query_file.read())

    if replacements:
        for k, v in replacements.items():
            raw_query = raw_query.replace(k, v)

    query = json.dumps({"query": raw_query})

    diagnostics.trace("Calling the following GraphQL query:")
    diagnostics.trace(query)

    response = requests.post(
        url=config.GITHUB_API_V4_ENDPOINT,
        data=query,
        headers={
            "User-Agent": "venturesomestone",
            "Accept": "application/json",
            "Authorization": "bearer {}".format(data.build.github_token)})

    diagnostics.trace(
        "The query returned the following JSON:\n{}".format(response.json()))

    return response.json()["data"]


def find_release_node(key, json_data):
    """
    Finds the requested release node from the GitHub API JSON data.

    key -- the name of the product.
    json_data -- the JSON data where the release node is.
    """
    product = data.build.products[key]
    release_edges = json_data["repository"]["releases"]["edges"]
    ret_node = None
    gh_version = get_github_version(key)

    for edge in release_edges:
        node = edge["node"]
        if node["name"] == "":
            continue
        if node["name"] == gh_version:
            diagnostics.debug(
                "Found the release {} ({}) of {}".format(
                    product.version,
                    gh_version,
                    product.repr))
            ret_node = node

    return ret_node


def find_release_node_by_tag(key, json_data):
    """
    Finds the requested release node from the GitHub API JSON data by the tag
    name.

    key -- the name of the product.
    json_data -- the JSON data where the release node is.
    """
    product = data.build.products[key]
    release_edges = json_data["repository"]["releases"]["edges"]
    ret_node = None
    gh_version = get_github_version(key)

    for edge in release_edges:
        node = edge["node"]
        if node["name"] == "":
            continue
        tag_name = node["tag"]["name"]
        if tag_name == gh_version:
            diagnostics.debug(
                "Found the release {} ({}) of {}".format(
                    product.version,
                    gh_version,
                    product.repr))
            ret_node = node

    return ret_node
