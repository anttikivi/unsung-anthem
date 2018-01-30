#===--------------------------- cmake.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Ode and Unsung Anthem CMake
call.
"""


import platform

from build_utils import workspace

from script_support import data

from script_support.variables import ANTHEM_REPO_NAME


def construct_call(lib=False, test=False):
    """
    Construct the CMake call for building Ode and Unsung Anthem.
    """
    ode = data.build.products.ode
    anthem = data.build.products.anthem
    args = data.build.args
    toolchain = data.build.toolchain
    source_dir = workspace.source_dir(product=anthem, name=ANTHEM_REPO_NAME)

    cmake_call = [toolchain.cmake, source_dir, "-G", args.cmake_generator]

    if platform.system() == "Windows":
        local_root = data.build.local_root.replace("\\", "/")
    else:
        local_root = data.build.local_root

    cmake_call += [
        "-DCMAKE_INSTALL_PREFIX={}".format(data.build.install_root),
        "-DODE_INSTALL_PREFIX={}".format(local_root),
        "-DODE_CXX_VERSION={}".format(data.build.std),
        "-DODE_NAME={}".format(args.ode_name),
        "-DODE_TEST_EXECUTABLE_NAME={}".format(args.ode_test_executable_name),
        "-DANTHEM_EXECUTABLE_NAME={}".format(args.executable_name),
        "-DANTHEM_LIB_NAME={}".format(args.lib_name),
        "-DANTHEM_TEST_EXECUTABLE_NAME={}".format(args.test_executable_name),
        "-DODE_MAIN_COMPILER_TOOL={}".format(args.main_tool),
        "-DODE_LOGGER_NAME={}".format(ode.logger_name),
        "-DANTHEM_LOGGER_NAME={}".format(anthem.logger_name),
        "-DODE_OPENGL_VERSION_MAJOR={}".format(ode.opengl.version.major),
        "-DODE_OPENGL_VERSION_MINOR={}".format(ode.opengl.version.minor),
        "-DANTHEM_WINDOW_NAME={}".format(anthem.window_name)
    ]

    if not args.build_anthem:
        cmake_call += ["-DODE_ONLY={}".format("ON")]

    # TODO
    # cmake_call += ["-DANTHEM_SDL_VERSION={}".format(
    #     data.build.products.sdl.version)]

    if args.ode_assertions:
        cmake_call += ["-DODE_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_call += ["-DODE_ENABLE_ASSERTIONS=OFF"]

    if args.anthem_assertions:
        cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=OFF"]

    if not test and not lib:
        cmake_call += ["-DODE_EXECUTABLE_TYPE=lib"]
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE=exe"]
    elif lib and not test:
        cmake_call += ["-DODE_EXECUTABLE_TYPE=lib"]
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE=lib"]
    elif test and not lib:
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE=test"]
        cmake_call += ["-DODE_EXECUTABLE_TYPE=test"]

    if args.cmake_generator == "Ninja":
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]

    if data.build.stdlib:
        cmake_call += ["-DODE_STDLIB={}".format(data.build.stdlib)]

    if args.build_llvm or args.build_libcxx:
        cmake_call += ["-DCMAKE_CXX_FLAGS=-I{}/include/c++/v1".format(
            local_root)]
        cmake_call += ["-DODE_LINK_LIBCXX=ON"]

    if args.enable_gcov:
        cmake_call += ["-DODE_ENABLE_GCOV=ON"]
        cmake_call += ["-DCMAKE_BUILD_TYPE=Coverage"]
    else:
        cmake_call += ["-DODE_ENABLE_GCOV=OFF"]
        if args.build_anthem:
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.anthem_build_variant
            )]
        else:
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.ode_build_variant
            )]

    if args.multithreading:
        cmake_call += ["-DODE_MULTITHREADING=ON"]
    else:
        cmake_call += ["-DODE_MULTITHREADING=OFF"]

    if data.build.ci and not platform.system() == "Darwin":
        cmake_call += ["-DODE_MANUAL_SDL=ON"]

    if args.extra_cmake_options:
        cmake_call += args.extra_cmake_options

    return cmake_call
