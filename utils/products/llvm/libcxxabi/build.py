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
The support module containing the utilities for libc++abi build.
"""


import os

from build_utils import shell, workspace

from products import common

from script_support import data


def set_up():
    """
    Set up the libc++abi source for the build.
    """
    product = data.build.products.llvm
    key = product.subprojects["libcxxabi"]

    common.build.check_source(product=product, subproject=key)

    source_dir = workspace.source_dir(product=product, subproject=key)

    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "projects",
        key
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "projects",
        key
    ))


def copy_dynamic(dest):
    """
    Move the dynamic library.

    dest -- the directory to which the library is copied.
    """
    bin_path = workspace.lib_file(path="libc++abi.dylib")
    dest_path = os.path.join(dest, "libc++abi.dylib")
    if os.path.exists(dest_path):
        return
    shell.copy(bin_path, dest)

    bin_path = workspace.lib_file(path="libc++abi.1.dylib")
    dest_path = os.path.join(dest, "libc++abi.1.dylib")
    shell.copy(bin_path, dest)

    bin_path = workspace.lib_file(path="libc++abi.1.0.dylib")
    dest_path = os.path.join(dest, "libc++abi.1.0.dylib")
    shell.copy(bin_path, dest)
