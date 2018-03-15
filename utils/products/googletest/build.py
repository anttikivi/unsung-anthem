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


from __future__ import print_function

import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def _build():
    product = data.build.products.googletest
    common.build.check_source(product)
    bin_path = os.path.join(data.build.local_root, "lib", "libgoogletest.a")
    build_dir = workspace.build_dir(product)
    if common.build.binary_exists(product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    common.build.build_call(product=product, cmake_args={
        "CMAKE_CXX_FLAGS": "/D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
    }, solution_name="gtest", source_subdir="googletest")


def do_build():
    """Build Google Test."""
    product = data.build.products.googletest
    common.build.check_source(product)
    if platform.system() == "Windows":
        bin_path = os.path.join(data.build.local_root, "lib", "googletest.lib")
    else:
        bin_path = os.path.join(
            data.build.local_root, "lib", "libgoogletest.a")
    build_dir = workspace.build_dir(product)
    if common.build.binary_exists(product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    if platform.system() == "Windows":
        common.build.build_call(product=product, cmake_args={
            "CMAKE_CXX_FLAGS": "/D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
        }, solution_name="gtest", source_subdir="googletest")
    else:
        common.build.build_call(
            product=product, solution_name="gtest", source_subdir="googletest")
    for dirpath, dirnames, filenames in os.walk(build_dir):
        print("Now going through directory '{}'".format(dirpath))
        for name in filenames:
            path = os.path.join(dirpath, name)
            print(path)


def should_build():
    """Check whether this product should be built."""
    return True
