#===-------------------------- github_v4_util.py -------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
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

from script_support import data

from script_support.defaults import GITHUB_API_V4_ENDPOINT

from script_support.variables import SCRIPT_DIR


def get_github_version(product):
    """Concatenate the full version for GitHub."""
    github_data = product.github_data
    if github_data.version_prefix:
        ret = "{}{}".format(github_data.version_prefix, product.version)
    else:
        ret = product.version
    return ret


def call_query(file_name, replacements=None):
    """Calls the given GraphQL query."""
    with open(os.path.join(SCRIPT_DIR, file_name)) as query_file:
        raw_query = str(query_file.read())
    if replacements:
        for k, v in replacements.items():
            raw_query = raw_query.replace(k, v)
    diagnostics.trace("Calling the following GraphQL query:\n{}".format(
        raw_query))
    query = json.dumps({"query": raw_query})
    response = requests.post(
        url=GITHUB_API_V4_ENDPOINT,
        data=query,
        headers={
            "User-Agent": "venturesomestone", "Accept": "application/json",
            "Authorization": "bearer {}".format(data.build.github_token)
        })

    diagnostics.trace("The response of the query was:\n{}".format(
        response.json()))

    return response.json()["data"]


def find_release_node(product, json_data, let_use_fallback=False):
    """Finds the requested release node from the GitHub API JSON data."""
    release_edges = json_data["repository"]["releases"]["edges"]
    ret_node = None
    gh_version = get_github_version(product)
    for edge in release_edges:
        node = edge["node"]
        if node is None or node["name"] == "":
            continue
        if node["name"] == gh_version:
            diagnostics.debug("Found the release {} ({}) of {}".format(
                product.version, gh_version, product.repr))
            ret_node = node

    if not ret_node and let_use_fallback:
        return release_edges[0]["node"]

    return ret_node


def find_release_node_by_tag(product, json_data):
    """
    Finds the requested release node from the GitHub API JSON data by the tag
    name."""
    release_edges = json_data["repository"]["releases"]["edges"]
    ret_node = None
    gh_version = get_github_version(product)
    for edge in release_edges:
        node = edge["node"]
        if node is None or node["name"] == "":
            continue
        tag_name = node["tag"]["name"]
        if tag_name == gh_version:
            diagnostics.debug("Found the release {} ({}) of {}".format(
                product.version, gh_version, product.repr))
            ret_node = node
    return ret_node
