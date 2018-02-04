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

from build_utils import shell, workspace

from products import common

from script_support import data


def do_build():
    """
    Build hayai.
    """
    product = data.build.products.hayai
    common.build.check_source(product)
    bin_path = os.path.join(data.build.local_root, "lib", "libhayai_main.a")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(product)

    shell.makedirs(build_dir)

    cmake_args = {
        "INSTALL_LIB_DIR": os.path.join(data.build.local_root, "lib"),
        "INSTALL_BIN_DIR": os.path.join(data.build.local_root, "bin"),
        "INSTALL_INCLUDE_DIR": os.path.join(data.build.local_root, "include")
    }

    common.build.build_call(product=product, cmake_args=cmake_args)


def should_build():
    """
    Check whether this product should be built.
    """
    return data.build.args.build_test
