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

from .product import binary_exists, build_call, check_source

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


def do_build(build_data):
    """
    Do the build of libc++.

    build_data -- the build data.
    """
    args = build_data.args
    product = build_data.products.llvm
    bin_path = libcxx_bin_path(build_data=build_data)
    build_dir = workspace.build_dir(
        build_data=build_data, product=product, subproduct="libcxx"
    )
    check_source(product=product, subproduct="libcxx")
    if binary_exists(
            build_data=build_data, product=product, path=bin_path,
            subproduct="libcxx"):
        return
    shell.makedirs(build_dir)

    cmake_args = []

    if args.libcxx_assertions:
        cmake_args += ["-DLIBCXX_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_args += ["-DLIBCXX_ENABLE_ASSERTIONS=OFF"]

    build_call(
        build_data=build_data, product=product, subproduct="libcxx",
        cmake_args=cmake_args
    )


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
