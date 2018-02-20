#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for Google Test build."""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def do_build():
    """Build Google Test."""
    product = data.build.products.googletest
    common.build.check_source(product)
    bin_path = os.path.join(data.build.local_root, "lib", "libgoogletest.a")
    build_dir = workspace.build_dir(product)
    if common.build.binary_exists(product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    common.build.build_call(product=product, cmake_args={
        # "BENCHMARK_USE_LIBCXX": True,
        # "CMAKE_CXX_FLAGS": "-I/usr/local/include/c++/v1"
    })


def should_build():
    """Check whether this product should be built."""
    return True
