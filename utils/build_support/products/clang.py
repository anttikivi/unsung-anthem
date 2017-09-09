#===--------------------------- clang.py ----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the Clang product helpers.
"""


import os
import platform

from .product import check_source

from .. import diagnostics, shell, workspace


def clang_bin_path(build_data):
    if platform.system() == "Windows":
        # TODO
        return os.path.join(build_data.install_root, "bin", "clang")
    else:
        return os.path.join(build_data.install_root, "bin", "clang")


def clang_cxx_bin_path(build_data):
    if platform.system() == "Windows":
        # TODO
        return os.path.join(build_data.install_root, "bin", "clang++")
    else:
        return os.path.join(build_data.install_root, "bin", "clang++")


def set_up(build_data):
    """
    """
    product = build_data.products.llvm
    check_source(product=product, subproduct="clang")
    source_dir = workspace.source_dir(product=product, subproduct="clang")
    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproduct="llvm"), "tools",
        "clang"
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproduct="llvm"), "tools",
        "clang"
    ))
