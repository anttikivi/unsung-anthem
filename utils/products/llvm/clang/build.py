#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
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


def set_up():
    """
    Set up the libc++abi source for the build.
    """
    product = data.build.products.llvm
    key = "clang"  # product.subprojects["clang"]

    common.build.check_source(key=product.identifier, subproject=key)

    source_dir = workspace.source_dir(product=product, subproject=key)

    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "tools",
        key
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "tools",
        key
    ))
