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
The support module containing the utilities for Clang build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def clang_bin_path():
    """
    Create the path for the binary of Clang.
    """
    if platform.system() == "Windows":
        # TODO
        return os.path.join(data.build.local_root, "bin", "clang")
    else:
        return os.path.join(data.build.local_root, "bin", "clang")


def clang_cxx_bin_path():
    """
    Create the path for the C++ compiler binary of Clang.
    """
    if platform.system() == "Windows":
        # TODO
        return os.path.join(data.build.local_root, "bin", "clang++")
    else:
        return os.path.join(data.build.local_root, "bin", "clang++")


def remove_set_up():
    """
    Remove the Clang source from the build.
    """
    product = data.build.products.llvm
    key = "clang"  # product.subprojects["clang"]

    dest = os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "tools",
        key
    )

    if not os.path.isdir(dest):
        return

    shell.rmtree(dest)


def set_up():
    """
    Set up the Clang source for the build.
    """
    product = data.build.products.llvm
    key = "clang"  # product.subprojects["clang"]

    common.build.check_source(product=product, subproject=key)

    source_dir = workspace.source_dir(product=product, subproject=key)

    remove_set_up()

    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "tools",
        key
    ))
