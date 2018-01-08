#===------------------------- github_tag.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for downloading a tag from GitHub.
"""


import os
import platform

from build_utils import diagnostics, shell

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT

from . import github_v4_util


TAG_QUERY_GRAPHQL = "github_tag.graphql"


def checkout_tag_windows(key, tag_ref_name):
    """
    Checkout a tag.

    key -- the name of the product.
    tag_ref_name -- the name of the tag.
    """
    with shell.pushd(os.path.join(
            ANTHEM_SOURCE_ROOT,
            key,
            data.build.products[key].version)):
        shell.call([
            data.build.toolchain.git, "checkout",
            "tags/{}".format(tag_ref_name), "-b",
            "{}_anthem_branch".format(tag_ref_name)])


def checkout_tag(key, tag_ref_name):
    """
    Checkout a tag.

    key -- the name of the product.
    tag_ref_name -- the name of the tag.
    """
    with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", key)):
        shell.call([
            data.build.toolchain.git, "checkout",
            "tags/{}".format(tag_ref_name), "-b",
            "{}_anthem_branch".format(tag_ref_name)])


def download_v4(key):
    """
    Download a tag from GitHub.

    key -- the name of the product.
    """
    product = data.build.products[key]
    github_data = product.github_data

    response_json_data = github_v4_util.call_query(TAG_QUERY_GRAPHQL, {
        "{REPOSITORY_OWNER}": github_data.owner,
        "{REPOSITORY_NAME}": github_data.name
    })

    if platform.system() == "Windows":
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key)):
            shell.call([
                data.build.toolchain.git, "clone",
                "{}.git".format(response_json_data["repository"]["url"]),
                product.version])
    else:
        with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp")):
            shell.call([
                data.build.toolchain.git, "clone",
                "{}.git".format(response_json_data["repository"]["url"])])

    release_node = github_v4_util.find_release_node(
        key,
        response_json_data)

    if not release_node:
        release_node = github_v4_util.find_release_node_by_tag(
            key,
            response_json_data
        )

    tag_ref_name = github_v4_util.get_github_version(key) \
        if not release_node \
        else release_node["tag"]["name"]

    if platform.system() == "Windows":
        checkout_tag_windows(key=key, tag_ref_name=tag_ref_name)
    else:
        checkout_tag(key=key, tag_ref_name=tag_ref_name)


def download(key):
    """
    Download a tag from GitHub.

    key -- the name of the product.
    """
    if data.build.github_token:
        download_v4(key=key)
    else:
        # TODO
        diagnostics.fatal("TODO")
