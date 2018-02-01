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
The support module containing the utilities for SDL build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def _build_windows():
    """
    Do the build of SDL on Windows.
    """
    product = data.build.products.sdl
    bin_path = workspace.lib_file(path="SDL2.lib")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    source_dir = workspace.source_dir(product)
    include_dir = workspace.include_file(path="SDL2")
    if not workspace.is_include_dir_made() \
            and workspace.include_file_exists(path="SDL2"):
        shell.rmtree(include_dir)
    shell.copytree(os.path.join(source_dir, "include"), include_dir)
    if not workspace.is_lib_dir_made():
        for lib_file in os.listdir(
                os.path.join(data.build.local_root, "lib")
        ):
            if "SDL" in lib_file:
                shell.rm(workspace.lib_file(path=lib_file))
    for lib_file in os.listdir(os.path.join(source_dir, "lib", "x86")):
        shell.copy(
            os.path.join(source_dir, "lib", "x86", lib_file),
            workspace.lib_file(path=lib_file)
        )


def _build():
    """
    Do the build of SDL.
    """
    product = data.build.products.sdl
    bin_path = os.path.join(data.build.local_root, "lib", "libSDL2d.a")
    build_dir = workspace.build_dir(product)
    if common.build.binary_exists(product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    common.build.build_call(product=product)


def do_build():
    """
    Build SDL.
    """
    product = data.build.products.sdl
    common.build.check_source(product.identifier)
    if platform.system() == "Windows":
        _build_windows()
    else:
        _build()


def should_build():
    """
    Check whether this product should be built.
    """
    return True


def copy_dynamic_windows(dest):
    """
    Move the dynamic library on Windows.

    dest -- the directory to which the library is copied.
    """
    bin_path = workspace.lib_file(path="SDL2.dll")
    dest_path = os.path.join(dest, "SDL2.dll")
    if os.path.exists(dest_path):
        return
    shell.copy(bin_path, dest)


def copy_dynamic(dest):
    """
    Move the dynamic library.

    dest -- the directory to which the library is copied.
    """
    if platform.system() == "Windows":
        copy_dynamic_windows(dest)
    else:
        bin_path = workspace.lib_file(path="libSDL2d.dylib")
        dest_path = os.path.join(dest, "libSDL2d.dylib")
        if os.path.exists(dest_path):
            return
        shell.copy(bin_path, dest)
