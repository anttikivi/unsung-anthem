#===--------------------------- cmake.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Unsung Anthem CMake call.
"""


import platform

from build_utils import workspace

from script_support import data

from script_support.variables import ANTHEM_REPO_NAME


def construct_call(tests=False):
    """
    Construct the CMake call for building Unsung Anthem.
    """
    product = data.build.products.anthem
    args = data.build.args
    toolchain = data.build.toolchain
    source_dir = workspace.source_dir(product=product, name=ANTHEM_REPO_NAME)

    cmake_call = [toolchain.cmake, source_dir, "-G", args.cmake_generator]

    if platform.system() == "Windows":
        local_root = data.build.local_root.replace("\\", "/")
    else:
        local_root = data.build.local_root

    cmake_call += [
        "-DCMAKE_INSTALL_PREFIX={}".format(data.build.install_root),
        "-DANTHEM_INSTALL_PREFIX={}".format(local_root),
        "-DANTHEM_CXX_VERSION={}".format(data.build.std),
        "-DANTHEM_EXECUTABLE_NAME={}".format(args.executable_name),
        "-DANTHEM_LIB_NAME={}".format(args.lib_name),
        "-DANTHEM_TEST_EXECUTABLE_NAME={}".format(args.test_executable_name),
        "-DANTHEM_MAIN_COMPILER_TOOL={}".format(args.main_tool),
        "-DANTHEM_LOGGER_NAME={}".format(product.logger_name),
        "-DANTHEM_INPUT_LOGGER_NAME={}-{}".format(
            product.logger_name, "input"
        ),
        "-DANTHEM_OPENGL_VERSION_MAJOR={}".format(
            product.opengl.version.major
        ),
        "-DANTHEM_OPENGL_VERSION_MINOR={}".format(
            product.opengl.version.minor
        ),
        "-DANTHEM_WINDOW_NAME={}".format(product.window_name)
    ]

    cmake_call += ["-DANTHEM_SDL_VERSION={}".format(
        data.build.products.sdl.version)]

    if args.anthem_assertions:
        cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=OFF"]

    if not tests:
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE=anthem"]
    else:
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE=test"]

    if args.cmake_generator == "Ninja":
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]

    if data.build.stdlib:
        cmake_call += ["-DANTHEM_STDLIB={}".format(data.build.stdlib)]

    if args.build_llvm or args.build_libcxx:
        cmake_call += ["-DCMAKE_CXX_FLAGS=-I{}/include/c++/v1".format(
            local_root)]
        cmake_call += ["-DANTHEM_LINK_CXXABI=ON"]

    if args.enable_gcov:
        cmake_call += ["-DANTHEM_ENABLE_GCOV=ON"]
        cmake_call += ["-DCMAKE_BUILD_TYPE=Coverage"]
    else:
        cmake_call += ["-DANTHEM_ENABLE_GCOV=OFF"]
        cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
            args.anthem_build_variant
        )]

    if args.multithreading:
        cmake_call += ["-DANTHEM_MULTITHREADING=ON"]
    else:
        cmake_call += ["-DANTHEM_MULTITHREADING=OFF"]

    if args.extra_cmake_options:
        cmake_call += args.extra_cmake_options

    return cmake_call
