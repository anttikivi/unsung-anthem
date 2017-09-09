#===--------------------------- glfw.py -----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the GLFW product helpers.
"""


import os
import platform

from .product import binary_exists, build_call, check_source

from .. import diagnostics, shell, workspace

from ..variables import ANTHEM_SOURCE_ROOT


def move_checkout_files(build_data):
    """
    Move the GLFW files from the default location of the checkout to the
    correct location.

    build_data -- the build data.
    """
    product = build_data.products.glfw
    version = product.version

    diagnostics.debug("Moving {} files".format(product.repr))

    shell.copytree(
        os.path.join(
            ANTHEM_SOURCE_ROOT, "glfw", version, "glfw-{}".format(version)),
        os.path.join(ANTHEM_SOURCE_ROOT, "glfw", "temp"))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "glfw", version))
    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "glfw", "temp"),
        os.path.join(ANTHEM_SOURCE_ROOT, "glfw", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "glfw", "temp"))

    diagnostics.debug_ok("Moved {} files".format(product.repr))


def do_build_windows(build_data):
    product = build_data.products.glfw
    bin_path = workspace.lib_file(build_data=build_data, path="glfw3.lib")
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    source_dir = workspace.source_dir(product=product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    include_dir = workspace.include_file(build_data=build_data, path="GLFW")
    if not workspace.is_include_dir_made(build_data=build_data) \
            and workspace.include_file_exists(
                build_data=build_data, path="GLFW"):
        shell.rmtree(include_dir)
    shell.copytree(os.path.join(build_dir, "include"), include_dir)
    if not workspace.is_lib_dir_made(build_data):
        for lib_file in os.listdir(
                os.path.join(build_data.install_root, "lib")):
            if "glfw" in lib_file:
                shell.rm(workspace.lib_file(
                    build_data=build_data, path=lib_file
                ))
    for lib_file in os.listdir(os.path.join(build_dir, "lib-vc2015")):
        shell.copy(
            os.path.join(build_dir, "lib-vc2015", lib_file),
            workspace.lib_file(build_data=build_data, path=lib_file)
        )


def do_build(build_data):
    args = build_data.args
    toolchain = build_data.toolchain
    product = build_data.products.glfw
    bin_path = workspace.lib_file(build_data=build_data, path="libglfw3.a")
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    shell.makedirs(build_dir)

    cmake_args = []

    if "clang" in toolchain.cc and args.ci:
        cmake_args += ["-DCMAKE_CXX_FLAGS=-stdlib=libc++"]

    build_call(build_data=build_data, product=product, cmake_args=cmake_args)


def build(build_data):
    """
    """
    product = build_data.products.llvm
    check_source(product=product)
    if platform.system() == "Windows":
        do_build_windows(build_data=build_data)
    else:
        do_build(build_data=build_data)
