#===---------------------------- github_tag.py ---------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for downloading a tag from GitHub.
"""


import os
import platform

from build_utils import diagnostics, shell, workspace

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT

from . import github_v4_util


TAG_QUERY_GRAPHQL = "github_tag.graphql"


def checkout_tag_windows(product, tag_ref_name):
    """Checkout a tag."""
    with shell.pushd(workspace.source_dir(product=product)):
        shell.call([
            data.build.toolchain.git, "checkout",
            "tags/{}".format(tag_ref_name), "-b",
            "{}_anthem_branch".format(tag_ref_name)
        ])


def checkout_tag(product, tag_ref_name):
    """Checkout a tag."""
    key = product.key
    with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", key)):
        shell.call([
            data.build.toolchain.git, "checkout",
            "tags/{}".format(tag_ref_name), "-b",
            "{}_anthem_branch".format(tag_ref_name)
        ])


def download_v4(product):
    """Download a tag from GitHub."""
    github_data = product.github_data
    response_json_data = github_v4_util.call_query(TAG_QUERY_GRAPHQL, {
        "{REPOSITORY_OWNER}": github_data.owner,
        "{REPOSITORY_NAME}": github_data.name
    })

    if platform.system() == "Windows":
        source_dir = workspace.source_dir(product=product)
        head, tail = os.path.split(source_dir)
        with shell.pushd(head):
            shell.call([data.build.toolchain.git, "clone", "{}.git".format(
                response_json_data["repository"]["url"]), tail])
    else:
        with shell.pushd(
                os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp")):
            shell.call([data.build.toolchain.git, "clone", "{}.git".format(
                response_json_data["repository"]["url"])])
    release_node = github_v4_util.find_release_node(
        product, response_json_data)

    if not release_node:
        release_node = github_v4_util.find_release_node_by_tag(
            product, response_json_data)

    tag_ref_name = github_v4_util.get_github_version(product) \
        if not release_node else release_node["tag"]["name"]

    if platform.system() == "Windows":
        checkout_tag_windows(product=product, tag_ref_name=tag_ref_name)
    else:
        checkout_tag(product=product, tag_ref_name=tag_ref_name)


def download(product):
    """Download a tag from GitHub."""
    if data.build.github_token:
        download_v4(product=product)
    else:
        # TODO
        diagnostics.fatal("TODO")
