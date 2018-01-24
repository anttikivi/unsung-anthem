#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for LLVM build.
"""


import os

from build_utils import diagnostics, shell, workspace

from products import common

from script_support import data

from . import clang, libcxx, libcxxabi


def _set_up_binary():
    """
    Set up the pre-built LLVM binary.
    """
    product = data.build.products.llvm
    bin_path = clang.clang_bin_path()

    if common.build.binary_exists(
            product=product,
            path=bin_path,
            subproject="llvm"):
        return

    build_dir = workspace.build_dir(product=product, subproject="llvm")

    diagnostics.debug("The build directory of LLVM is {}".format(build_dir))

    source_dir = workspace.source_dir(product=product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)

    shell.copytree(
        os.path.join(build_dir, "bin"),
        os.path.join(data.build.local_root, "bin")
    )
    shell.copytree(
        os.path.join(build_dir, "include"),
        os.path.join(data.build.local_root, "include")
    )
    shell.copytree(
        os.path.join(build_dir, "lib"),
        os.path.join(data.build.local_root, "lib")
    )
    shell.copytree(
        os.path.join(build_dir, "libexec"),
        os.path.join(data.build.local_root, "libexec")
    )
    shell.copytree(
        os.path.join(build_dir, "share"),
        os.path.join(data.build.local_root, "share")
    )


def _build():
    """
    Build the LLVM from source.
    """
    args = data.build.args
    product = data.build.products.llvm
    bin_path = clang.clang_bin_path()
    key = product.identifier

    build_dir = workspace.build_dir(product=product, subproject=key)

    if common.build.binary_exists(
            product=product,
            path=bin_path,
            subproject=key):
        return

    libcxx.set_up()
    libcxxabi.set_up()
    clang.set_up()

    shell.makedirs(build_dir)

    cmake_args = {"LIBCXX_ENABLE_ASSERTIONS": args.libcxx_assertions}

    common.build_call(product=product, subproject=key, cmake_args=cmake_args)


def do_build():
    """
    Build LLVM.
    """
    product = data.build.products.llvm
    args = data.build.args
    key = product.identifier

    common.build.check_source(key=key, subproject=key)

    if args.build_llvm and not args.build_libcxx:
        bin_path = clang.clang_bin_path()

        if common.build.binary_exists(
                product=product,
                path=bin_path,
                subproject=key):
            return

        if not args.source_llvm:
            _set_up_binary()
        else:
            _build()

        data.build.toolchain.cc = clang.clang_bin_path()
        data.build.toolchain.cxx = clang.clang_cxx_bin_path()
        data.build.args.main_tool = key
    elif not args.build_llvm and args.build_libcxx:
        libcxx.build.do_build()


def is_tool():
    """
    Check whether LLVM is considered to be a tool in this configuration.
    """
    diagnostics.trace("Checking if LLVM is considered to be a tool")
    if data.build.args.build_llvm:
        diagnostics.trace("LLVM is a tool")
        return True
    diagnostics.trace("LLVM is a not tool")
    return False


def should_build():
    """
    Check whether this product should be built.
    """
    return data.build.args.build_llvm or data.build.args.build_libcxx
