#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for CMake build.
"""


import os
import platform

from build_utils import diagnostics, shell, workspace

from products import common

from script_support import data


def cmake_bin_path():
    """
    Create the path for the binary of CMake.
    """
    if platform.system() == "Windows":
        return os.path.join(data.build.local_root, "bin", "cmake.exe")
    elif platform.system() == "Linux":
        return os.path.join(data.build.local_root, "bin", "cmake")
    elif platform.system() == "Darwin":
        return os.path.join(
            data.build.local_root,
            "CMake.app",
            "Contents",
            "bin",
            "cmake")
    diagnostics.fatal(
        "{} is not supported for {}".format(
            platform.system(), data.build.products.cmake.repr))


def do_build():
    """
    Builds CMake.
    """
    product = data.build.products.cmake

    data.build.toolchain.cmake = cmake_bin_path()

    common.build.check_source("cmake")

    bin_path = cmake_bin_path()
    build_dir = workspace.build_dir(product=product, target="build")

    if common.build.binary_exists(
            product=product,
            path=bin_path,
            target="build"):
        return

    source_dir = workspace.source_dir(product=product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    if platform.system() == "Darwin":
        shell.copytree(
            os.path.join(build_dir, "CMake.app"),
            os.path.join(data.build.local_root, "CMake.app"))
    else:
        shell.copytree(build_dir, data.build.local_root)


def should_build():
    """
    Check whether or not this product should be built.
    """
    return data.build.args.build_cmake or data.build.toolchain.cmake is None
