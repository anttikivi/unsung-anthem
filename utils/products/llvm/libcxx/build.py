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
The support module containing the utilities for libc++ build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from products.llvm import clang, libcxxabi

from script_support import data


def libcxx_bin_path():
    """
    Create the path for the binary of libc++.
    """
    if platform.system() == "Windows":
        # TODO
        return os.path.join(data.build.local_root, "lib", "libc++.a")
    else:
        return os.path.join(data.build.local_root, "lib", "libc++.a")


def set_up():
    """
    Set up the libc++ source for the build.
    """
    product = data.build.products.llvm
    key = product.subprojects["libcxx"]

    common.build.check_source(key=product.identifier, subproject=key)

    source_dir = workspace.source_dir(product=product, subproject=key)

    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "projects",
        key
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "projects",
        key
    ))


def do_build():
    """
    Build libcxx.
    """
    product = data.build.products.llvm
    args = data.build.args
    key = product.identifier
    bin_path = libcxx_bin_path()

    build_dir = workspace.build_dir(product=product, subproject=key)

    if common.build.binary_exists(
            product=product,
            path=bin_path,
            subproject=key):
        return

    set_up()
    libcxxabi.set_up()

    clang.build.remove_set_up()

    shell.makedirs(build_dir)

    cmake_args = {"LIBCXX_ENABLE_ASSERTIONS": args.libcxx_assertions}

    common.build_call(
        product=product,
        subproject=key,
        cmake_args=cmake_args,
        build_targets="cxx",
        install_targets=["install-cxx", "install-cxxabi"]
    )
