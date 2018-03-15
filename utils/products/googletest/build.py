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


def _copy_windows():
    product = data.build.products.googletest
    build_dir = workspace.build_dir(product)
    if not workspace.is_lib_dir_made():
        if os.path.exists(workspace.lib_file(path="gtest.lib")):
            shell.rm(workspace.lib_file(path="gtest.lib"))
    shell.copy(
        os.path.join(build_dir, "Debug", "gtest.lib"),
        workspace.lib_file(path="gtest.lib"))
    if not workspace.is_lib_dir_made():
        if workspace.include_file_exists(path="gtest"):
            shell.rmtree(workspace.include_file(path="gtest"))
    source_dir = workspace.source_dir(product=product)
    shell.copytree(
        os.path.join(source_dir, "googletest", "include", "gtest"),
        os.path.join(data.build.local_root, "include", "gtest"))
    for dirpath, dirnames, filenames in os.walk(data.build.local_root):
        print("Now going through directory '{}'".format(dirpath))
        for name in filenames:
            path = os.path.join(dirpath, name)
            print(path)


def do_build():
    """Build Google Test."""
    product = data.build.products.googletest
    common.build.check_source(product)
    if platform.system() == "Windows":
        bin_path = os.path.join(data.build.local_root, "lib", "gtest.lib")
    else:
        bin_path = os.path.join(
            data.build.local_root, "lib", "libgtest.a")
    build_dir = workspace.build_dir(product)
    if common.build.binary_exists(product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    if platform.system() == "Windows":
        common.build.build_call(product=product, cmake_args={
            "CMAKE_CXX_FLAGS": "/D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING"
        }, solution_name="gtest", source_subdir="googletest")
        _copy_windows()
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
