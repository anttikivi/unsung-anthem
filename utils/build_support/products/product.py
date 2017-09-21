#===-------------------------- product.py --------------------*- python -*-===#
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


def binary_exists(build_data, product, path, target=None, subproduct=None):
    """
    Check if the binary for the product exists.

    build_data -- the build data.
    product -- the product.
    path -- the path to the binary.
    target -- a custom target of the product.
    subproduct -- a possible subproduct which should be checked instead.
    """
    build_dir = workspace.build_dir(
        build_data=build_data, target=target, product=product,
        subproduct=subproduct
    )
    if os.path.exists(path) and os.path.exists(build_dir):
        if subproduct:
            diagnostics.debug_note(
                "{} ({}) is already built and should not be re-built".format(
                    subproduct, product.repr
                )
            )
        else:
            diagnostics.debug_note(
                "{} is already built and should not be re-built".format(
                    product.repr
                )
            )
        return True
    return False


def check_source(product, subproduct=None, name=None):
    """
    Check if the source directory of the product exists.

    product -- the product.
    subproduct -- a possible subproduct of the product for which the path is
    checked.
    name -- a custom name of the source directory.
    """
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
    elif name:
        source_dir = workspace.source_dir(product=product, name=name)
        if not os.path.exists(source_dir):
            diagnostics.fatal(
                "Cannot find source directory for {} (tried {})".format(
                    product.repr, source_dir
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


def build_call(
        build_data, product, subproduct=None, cmake_args=None,
        build_targets=None, install_targets=None):
    """
    Do a simple CMake call, followed by Ninja or Make calls, to build the
    given product.

    build_data -- the build data.
    product -- the product.
    subproduct -- a possible subproduct of the product which is built.
    cmake_args -- extra CMake arguments to be passed to the call.
    build_targets -- optional custom target to be used in the build.
    install_targets -- optional custom target to be used in the installation.
    """
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
            if build_targets:
                shell.ninja(build_data=build_data, target=build_targets)
            else:
                shell.ninja(build_data=build_data)
            if install_targets:
                shell.ninja(build_data=build_data, target=install_targets)
            else:
                shell.ninja_install(build_data=build_data)
        elif args.cmake_generator == "Unix Makefiles":
            if build_targets:
                shell.make(build_data=build_data, target=build_targets)
            else:
                shell.make(build_data=build_data)
            if install_targets:
                shell.make(build_data=build_data, target=install_targets)
            else:
                shell.make_install(build_data=build_data)


def copy_build(build_data, product, subdir=None):
    """
    Do a simple copying of files to the correct places for the Unsung Anthem
    build.

    build_data -- the build data.
    product -- the product.
    subdir -- a subdir in the project build directory which should be copied
    instead of the whole directory.
    """
    check_source(product=product)
    bin_path = workspace.include_dir(build_data=build_data, product=product)
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    source_dir = workspace.source_dir(product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    if not workspace.is_include_dir_made(build_data=build_data) \
            and workspace.include_dir_exists(
                build_data=build_data, product=product):
        shell.rmtree(bin_path)
    if subdir:
        shell.copytree(os.path.join(build_dir, subdir), bin_path)
    else:
        shell.copytree(build_dir, bin_path)
