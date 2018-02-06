#===----------------------------- checkout.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Lua checkout.
"""


import os
import platform

from build_utils import diagnostics, http_stream, shell, workspace

from products import common

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT


def move_files():
    """
    Move the Lua files to the correct location after the download.
    """
    product = data.build.products.lua
    version = product.version
    subdir = "{}-{}".format(product.key, version)
    shell.rmtree(workspace.source_dir(product=product))

    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir)
    )

    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp", subdir),
        workspace.source_dir(product=product)
    )
    if not platform.system() == "Windows" and not data.build.ci:
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))


def get_dependency():
    """
    Download Lua.
    """
    product = data.build.products.lua

    common.checkout.clean_checkout(product)

    version = product.version

    url = product.url_format.format(protocol="https", version=version)
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT,
        product.key,
        "temp",
        "lua-{}.tar.gz".format(version)
    )

    http_stream.stream(url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp")
    )
    shell.rm(destination)
    move_files()

    if not platform.system() == "Windows" and not data.build.ci:
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))