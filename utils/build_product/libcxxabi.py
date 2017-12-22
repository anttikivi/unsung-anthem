#===-------------------------- libcxxabi.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the libc++abi product helpers.
"""


import os

from .product import check_source

from .. import shell, workspace


def set_up(build_data):
    """
    Set libc++abi up for the LLVM build.

    build_data -- the build data.
    """
    product = build_data.products.llvm
    check_source(product=product, subproduct="libcxxabi")
    source_dir = workspace.source_dir(product=product, subproduct="libcxxabi")
    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproduct="llvm"), "projects",
        "libcxxabi"
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproduct="llvm"), "projects",
        "libcxxabi"
    ))
