#===------------------------------- cmake.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Ode and Unsung Anthem CMake
call.
"""


import platform

from build_utils import diagnostics, workspace

from script_support import data

from script_support.variables import ANTHEM_REPO_NAME


def construct_call(is_ode=False, lib=False, test=False):
    """
    Construct the CMake call for building Ode and Unsung Anthem.

    is_ode -- whether or not this is build for only Ode.
    lib -- whether or not the library configuration of the build is used.
    test -- whether or not the test configuration of the build is used.
    """
    if lib and test:
        diagnostics.fatal(
            "The CMake script cannot build both 'lib' and 'test' "
            "configurations at the same time"
        )
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
        "-DODE_MAIN_COMPILER_TOOL={}".format(args.main_tool),
        "-DODE_LOGGER_NAME={}".format(ode.logger_name),
        "-DODE_WINDOW_NAME={}".format("ode_window"),
        "-DODE_OPENGL_VERSION_MAJOR={}".format(ode.opengl.version.major),
        "-DODE_OPENGL_VERSION_MINOR={}".format(ode.opengl.version.minor),
    ]

    if is_ode:
        cmake_call += ["-DBUILD_ODE={}".format("ON")]

        cmake_call += ["-DODE_NAME={}".format(args.ode_name)]
        cmake_call += ["-DODE_TEST_NAME={}".format(args.ode_test_name)]

        if lib:
            cmake_call += ["-DODE_TYPE=lib"]
        elif test:
            cmake_call += ["-DODE_TYPE=test"]
        else:
            cmake_call += ["-DODE_TYPE=lib"]
    else:
        cmake_call += ["-DBUILD_ODE={}".format("OFF")]

        cmake_call += ["-DANTHEM_LOGGER_NAME={}".format(anthem.logger_name)]
        cmake_call += ["-DANTHEM_WINDOW_NAME={}".format(anthem.window_name)]

        cmake_call += ["-DANTHEM_NAME={}".format(args.anthem_name)]
        cmake_call += ["-DANTHEM_LIB_NAME={}".format(args.anthem_lib_name)]
        cmake_call += ["-DANTHEM_TEST_NAME={}".format(args.anthem_test_name)]

        if args.anthem_assertions:
            cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=ON"]
        else:
            cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=OFF"]

        if lib:
            cmake_call += ["-DANTHEM_TYPE=lib"]
        elif test:
            cmake_call += ["-DANTHEM_TYPE=test"]
        else:
            cmake_call += ["-DANTHEM_TYPE=exe"]

    # TODO
    # cmake_call += ["-DANTHEM_SDL_VERSION={}".format(
    #     data.build.products.sdl.version)]

    if args.developer_build:
        cmake_call += ["-DODE_DEVELOPER=ON"]
        if not is_ode:
            cmake_call += ["-DANTHEM_DEVELOPER=ON"]
    else:
        cmake_call += ["-DODE_DEVELOPER=OFF"]
        cmake_call += ["-DANTHEM_DEVELOPER=OFF"]

    if args.ode_assertions:
        cmake_call += ["-DODE_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_call += ["-DODE_ENABLE_ASSERTIONS=OFF"]

    if args.cmake_generator == "Ninja":
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]

    if data.build.stdlib:
        cmake_call += ["-DODE_STDLIB={}".format(data.build.stdlib)]

        if data.build.stdlib == "libc++":
            cmake_call += ["-DCMAKE_CXX_FLAGS=-I{}/include/c++/v1".format(
                local_root
            )]

    if args.optimization_level:
        cmake_call += [
            "-DODE_OPTIMIZATION_LEVEL={}".format(args.optimization_level)
        ]

    if args.enable_gcov:
        cmake_call += ["-DODE_ENABLE_GCOV=ON"]
        cmake_call += ["-DCMAKE_BUILD_TYPE=Coverage"]
    else:
        cmake_call += ["-DODE_ENABLE_GCOV=OFF"]
        if is_ode:
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.ode_build_variant
            )]
        else:
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.anthem_build_variant
            )]

    if args.multithreading:
        cmake_call += ["-DODE_MULTITHREADING=ON"]
    else:
        cmake_call += ["-DODE_MULTITHREADING=OFF"]

    if data.build.ci:  # and not platform.system() == "Darwin":
        cmake_call += ["-DODE_MANUAL_SDL=ON"]

    manual_rpath_ci = data.build.ci and platform.system() == "Darwin"

    if manual_rpath_ci:
        cmake_call += ["-DODE_SET_RPATH=ON"]
    else:
        cmake_call += ["-DODE_SET_RPATH=OFF"]

    if data.build.lua_in_source:
        cmake_call += ["-DODE_ADD_LUA_SOURCE=ON"]
    else:
        cmake_call += ["-DODE_ADD_LUA_SOURCE=OFF"]

    if args.extra_cmake_options:
        cmake_call += args.extra_cmake_options

    return cmake_call
