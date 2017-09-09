#===--------------------------- product.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the product helpers.
"""


import os

from .. import diagnostics, shell, workspace


def binary_exists(build_data, product, path, subproduct=None):
    if subproduct:
        build_dir = workspace.build_dir(
            build_data=build_data, product=product, subproduct=subproduct
        )
        if os.path.exists(path) and os.path.exists(build_dir):
            diagnostics.debug_note(
                "{} ({}) is already built and, thus, should not be "
                "re-built".format(subproduct, product.repr)
            )
        return True
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    if os.path.exists(path) and os.path.exists(build_dir):
        diagnostics.debug_note(
            "{} is already built and, thus, should not be re-built".format(
                product.repr
            )
        )
        return True
    return False


def check_source(product, subproduct=None):
    if subproduct:
        source_dir = workspace.source_dir(
            product=product, subproduct=subproduct
        )
        if not os.path.exists(source_dir):
            diagnostics.fatal(
                "Cannot find source directory for {} ({}) (tried {})".format(
                    subproduct, product.repr, source_dir
                )
            )
    else:
        source_dir = workspace.source_dir(product)
        if not os.path.exists(source_dir):
            diagnostics.fatal(
                "Cannot find source directory for {} (tried {})".format(
                    product.repr, source_dir
                )
            )


def build_call(build_data, product, subproduct=None, cmake_args=None):
    if subproduct:
        source_dir = workspace.source_dir(
            product=product, subproduct=subproduct
        )
        build_dir = workspace.build_dir(
            build_data=build_data, product=product, subproduct=subproduct
        )
    else:
        source_dir = workspace.source_dir(product=product)
        build_dir = workspace.build_dir(build_data=build_data, product=product)
    args = build_data.args
    toolchain = build_data.toolchain
    use_ninja = \
        args.cmake_generator == "Ninja" or args.cmake_generator == "Xcode"

    if subproduct:
        build_type = getattr(args, "{}_build_variant".format(subproduct))
    else:
        build_type = getattr(
            args, "{}_build_variant".format(product.identifier)
        )

    cmake_call = [
        toolchain.cmake,
        source_dir,
        "-DCMAKE_INSTALL_PREFIX={}".format(build_data.install_root),
        "-DCMAKE_BUILD_TYPE={}".format(build_type)
    ]

    if use_ninja:
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]
        cmake_call += ["-G", "Ninja"]
    else:
        cmake_call += ["-G", args.cmake_generator]

    if cmake_args:
        cmake_call += cmake_args

    cmake_env = {"CC": toolchain.cc, "CXX": toolchain.cxx}

    with shell.pushd(build_dir):
        diagnostics.debug(
            "Calling CMake with the following call: {}".format(str(cmake_call))
        )
        shell.call(cmake_call, env=cmake_env)
        # TODO MSBuild
        if use_ninja:
            shell.ninja(build_data=build_data)
            shell.ninja_install(build_data=build_data)
        elif args.cmake_generator == "Unix Makefiles":
            shell.make(build_data=build_data)
            shell.make_install(build_data=build_data)