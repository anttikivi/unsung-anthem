#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Lua build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def _build_windows():
    """
    Do the build of Lua on Windows.
    """
    product = data.build.products.lua
    bin_path = os.path.join(data.build.local_root, "lib", "lua.lib")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(product)
    source_dir = workspace.source_dir(product=product)
    shell.makedirs(build_dir)
    shell.copytree(source_dir, build_dir)
    with shell.pushd(build_dir):
        common.build.make(target="windows")
        common.build.make(
            target="install",
            extra_args="INSTALL_TOP={}".format(data.build.local_root)
        )


def _build():
    """
    Do the build of Lua.
    """
    product = data.build.products.lua
    bin_path = os.path.join(data.build.local_root, "lib", "liblua.a")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(product)
    source_dir = workspace.source_dir(product=product)
    shell.makedirs(build_dir)
    shell.copytree(source_dir, build_dir)
    with shell.pushd(build_dir):
        if platform.system() == "Darwin":
            common.build.make(target="macosx")
        elif platform.system() == "Linux":
            common.build.make(target="linux")
        common.build.make(
            target="install",
            extra_args="INSTALL_TOP={}".format(data.build.local_root)
        )


def do_build():
    """
    Build Lua.
    """
    product = data.build.products.lua
    common.build.check_source(product)
    if platform.system() == "Windows":
        _build_windows()
    else:
        _build()


def should_build():
    """
    Check whether this product should be built.
    """
    return True
