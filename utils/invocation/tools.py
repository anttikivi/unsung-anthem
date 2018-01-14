#===--------------------------- xcrun.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for building the tools necessary
for the build.
"""


from build_utils import diagnostics, reflection

from script_support import data


def build_tools():
    """
    Builds the tools necessary for the build invocation.
    """
    args = data.build.args
    toolchain = data.build.toolchain
    cmake_requires_ninja = \
        args.cmake_generator == "Ninja" or args.cmake_generator == "Xcode"
    ninja_build_required = \
        args.build_ninja or (cmake_requires_ninja and toolchain.ninja is None)
    cmake_build_required = args.build_cmake or toolchain.cmake is None
    llvm_build_required = args.build_llvm or args.build_libcxx

    to_set_up = list()

    if ninja_build_required:
        to_set_up += ["ninja"]
    if cmake_build_required:
        to_set_up += ["cmake"]
    if llvm_build_required:
        to_set_up += ["llvm"]

    for tool in to_set_up:
        product = data.build.products[tool]
        reflection.product_build_call(product, "do_build")
        diagnostics.debug_ok("{} is now built".format(product.repr))
