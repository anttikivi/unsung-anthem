#===--------------------------- libcxx.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the libc++ product helpers.
"""


import os
import platform

from .product import check_source

from .. import shell, workspace


def libcxx_bin_path(build_data):
    """
    Create the path for the binary of libc++.

    build_data -- the build data.
    """
    if platform.system() == "Windows":
        # TODO
        return os.path.join(build_data.install_root, "lib", "libc++.a")
    return os.path.join(build_data.install_root, "lib", "libc++.a")


def set_up(build_data):
    """
    Set libc++ up for the LLVM build.

    build_data -- the build data.
    """
    product = build_data.products.llvm
    check_source(product=product, subproduct="libcxx")
    source_dir = workspace.source_dir(product=product, subproduct="libcxx")
    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproduct="llvm"), "projects",
        "libcxx"
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproduct="llvm"), "projects",
        "libcxx"
    ))
