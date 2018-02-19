#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for Google Benchmark build."""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def do_build():
    """Build Google Benchmark."""
    product = data.build.products.benchmark
    common.build.check_source(product)
    bin_path = os.path.join(data.build.local_root, "lib", "libbenchmark.a")
    build_dir = workspace.build_dir(product)
    if common.build.binary_exists(product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    common.build.build_call(product=product, cmake_args={
        "BENCHMARK_ENABLE_GTEST_TESTS": False
    })


def should_build():
    """Check whether this product should be built."""
    return True
