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
The support module containing the utilities for hayai build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def _build_simple():
    product = data.build.products.hayai
    source_dir = workspace.source_dir(product)
    include_dir = workspace.include_file(path=product.key)
    if not workspace.is_include_dir_made() \
            and workspace.include_file_exists(path=product.key):
        shell.rmtree(include_dir)
    shell.makedirs(include_dir)
    for header in os.listdir(os.path.join(source_dir, "src")):
        if not header.endswith(".cpp") and not header.endswith(".txt"):
            shell.copy(
                os.path.join(source_dir, "src", header),
                os.path.join(include_dir, header)
            )


def _build():
    product = data.build.products.hayai
    build_dir = workspace.build_dir(product)
    shell.makedirs(build_dir)
    cmake_args = {
        "INSTALL_LIB_DIR": os.path.join(data.build.local_root, "lib"),
        "INSTALL_BIN_DIR": os.path.join(data.build.local_root, "bin"),
        "INSTALL_INCLUDE_DIR": os.path.join(data.build.local_root, "include")
    }
    common.build.build_call(product=product, cmake_args=cmake_args)


def do_build():
    """
    Build hayai.
    """
    product = data.build.products.hayai
    common.build.check_source(product)
    bin_path = os.path.join(
        data.build.local_root,
        "include",
        product.key,
        "hayai.hpp"
    )
    if common.build.binary_exists(product=product, path=bin_path):
        return
    if platform.system() == "Windows":
        _build_simple()
    else:
        _build_simple()  # _build()


def should_build():
    """
    Check whether this product should be built.
    """
    return data.build.args.build_test and data.build.args.developer_build
