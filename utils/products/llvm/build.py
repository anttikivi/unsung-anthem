#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for LLVM build."""


import os
import platform

from build_utils import diagnostics, shell, workspace

from products import common

from script_support import data


def clang_bin_path():
    """Create the path for the binary of Clang."""
    return os.path.join(data.build.local_root, "bin", "clang")


def clangxx_bin_path():
    """Create the path for the binary of clang++."""
    return os.path.join(data.build.local_root, "bin", "clang++")


def do_build():
    """Builds LLVM."""
    product = data.build.products.llvm
    data.build.toolchain.cc = clang_bin_path()
    data.build.toolchain.cxx = clangxx_bin_path()
    common.build.check_source(product)
    bin_path = clang_bin_path()
    if common.build.binary_exists(product=product, path=bin_path):
        return
    source_dir = workspace.source_dir(product=product)
    shell.copytree(
        os.path.join(source_dir, "bin"),
        os.path.join(data.build.local_root, "bin"))
    shell.copytree(
        os.path.join(source_dir, "include"),
        os.path.join(data.build.local_root, "include"))
    shell.copytree(
        os.path.join(source_dir, "lib"),
        os.path.join(data.build.local_root, "lib"))
    shell.copytree(
        os.path.join(source_dir, "libexec"),
        os.path.join(data.build.local_root, "lib"))
    shell.copytree(
        os.path.join(source_dir, "share"),
        os.path.join(data.build.local_root, "share"))


def should_build():
    """Check whether or not this product should be built."""
    return data.build.args.build_llvm


def copy_dynamic(dest):
    """Move the dynamic library."""
    if platform.system() == "Darwin":
        extension = ".dylib"
    else:
        extension = ".so"

    for libfile in os.listdir(dest):
        if "libc++" in libfile and extension in libfile:
            shell.rm(os.path.join(dest, libfile))
    for libfile in os.listdir(os.path.join(data.build.local_root, "lib")):
        if "libc++" in libfile and extension in libfile:
            shell.copy(
                os.path.join(data.build.local_root, "lib", libfile),
                os.path.join(dest, libfile))
