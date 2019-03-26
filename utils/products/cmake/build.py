#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

"""
The support module containing the utilities for CMake build.
"""


import os
import platform

from build_utils import diagnostics, shell, workspace

from products import common

from script_support import data


def cmake_bin_path():
    """Create the path for the binary of CMake."""
    if platform.system() == "Windows":
        return os.path.join(data.build.local_root, "bin", "cmake.exe")
    elif platform.system() == "Linux":
        return os.path.join(data.build.local_root, "bin", "cmake")
    elif platform.system() == "Darwin":
        return os.path.join(
            data.build.local_root, "CMake.app", "Contents", "bin", "cmake")
    diagnostics.fatal("{} is not supported for {}".format(
        platform.system(), data.build.products.cmake.repr))


def do_build():
    """Builds CMake."""
    product = data.build.products.cmake
    data.build.toolchain.cmake = cmake_bin_path()
    common.build.check_source(product)
    bin_path = cmake_bin_path()
    if common.build.binary_exists(product=product, path=bin_path):
        return
    source_dir = workspace.source_dir(product=product)
    if platform.system() == "Darwin":
        shell.copytree(
            os.path.join(source_dir, "CMake.app"),
            os.path.join(data.build.local_root, "CMake.app"))
    else:
        shell.copytree(
            os.path.join(source_dir, "bin"),
            os.path.join(data.build.local_root, "bin"))
        shell.copytree(
            os.path.join(source_dir, "doc"),
            os.path.join(data.build.local_root, "doc"))
        shell.copytree(
            os.path.join(source_dir, "man"),
            os.path.join(data.build.local_root, "man"))
        shell.copytree(
            os.path.join(source_dir, "share"),
            os.path.join(data.build.local_root, "share"))


def should_build():
    """Check whether or not this product should be built."""
    return data.build.args.build_cmake or data.build.toolchain.cmake is None
