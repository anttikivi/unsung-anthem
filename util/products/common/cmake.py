#===------------------------------- cmake.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

"""
The support module containing the utilities for Obliging Ode and Unsung Anthem
CMake call.
"""


import os
import platform

from build_utils import diagnostics, reflection, workspace

from script_support import data

from script_support.defaults import COVERAGE_TARGET_MARK

from script_support.variables import ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME


def _config_value(name):
    return reflection.config_value(name)


def construct_call(is_ode=False, lib=False, test=False):
    """Construct the CMake call for building Ode and Unsung Anthem."""
    if lib and test:
        diagnostics.fatal(
            "The CMake script cannot build both 'lib' and 'test' "
            "configurations at the same time"
        )
    ode = data.build.products.ode
    anthem = data.build.products.anthem
    args = data.build.args
    toolchain = data.build.toolchain
    source_dir = os.path.join(ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME)

    cmake_call = [toolchain.cmake, source_dir, "-G", args.cmake_generator]

    if platform.system() == "Windows":
        local_root = data.build.local_root.replace("\\", "/")
    else:
        local_root = data.build.local_root

    install_root = data.build.install_root

    cmake_call += [
        "-DCMAKE_C_COMPILER={}".format(toolchain.cc),
        "-DCMAKE_CXX_COMPILER={}".format(toolchain.cxx),
        "-DCMAKE_INSTALL_PREFIX={}".format(install_root),
        "-DODE_INSTALL_PREFIX={}".format(local_root),
        "-DODE_BIN_DIR_NAME=bin",
        "-DODE_INCLUDE_DIR_NAME=include",
        "-DODE_LIB_DIR_NAME=lib",
        "-DODE_SCRIPT_DIR_NAME={}".format(
            _config_value("GCOV_SCRIPT_DIRECTORY_NAME")
            if args.enable_gcov and test
            else _config_value("SCRIPT_DIRECTORY_NAME")),
        "-DODE_CXX_VERSION={}".format(data.build.std),
        "-DODE_LOGGER_NAME={}".format(ode.logger_name),
        "-DODE_WINDOW_NAME={}".format("ode_window"),
        "-DODE_OPENGL_VERSION_MAJOR={}".format(ode.opengl.version.major),
        "-DODE_OPENGL_VERSION_MINOR={}".format(ode.opengl.version.minor),
        "-DODE_VERSION={}".format(args.ode_version),
        "-DANTHEM_VERSION={}".format(args.anthem_version)
    ]

    if args.verbose_cmake:
        cmake_call += ["-DODE_VERBOSE_BUILD=ON"]
    else:
        cmake_call += ["-DODE_VERBOSE_BUILD=OFF"]

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

    if args.developer_build:
        cmake_call += ["-DODE_DEVELOPER=ON"]
        if not is_ode:
            cmake_call += ["-DANTHEM_DEVELOPER=ON"]
    else:
        cmake_call += ["-DODE_DEVELOPER=OFF"]
        cmake_call += ["-DANTHEM_DEVELOPER=OFF"]

    if args.disable_gl_calls:
        cmake_call += ["-DODE_DISABLE_GL_CALLS=ON"]
    else:
        cmake_call += ["-DODE_DISABLE_GL_CALLS=OFF"]

    if args.build_benchmarking and test and not args.enable_gcov:
        cmake_call += ["-DODE_TEST_BENCHMARKING=ON"]
        if not is_ode:
            cmake_call += ["-DANTHEM_TEST_BENCHMARKING=ON"]
        if args.build_separate_benchmark_library:
            cmake_call += ["-DODE_ADD_BENCHMARK_SOURCE=OFF"]
        else:
            cmake_call += ["-DODE_ADD_BENCHMARK_SOURCE=ON"]
    else:
        cmake_call += ["-DODE_TEST_BENCHMARKING=OFF"]
        cmake_call += ["-DANTHEM_TEST_BENCHMARKING=OFF"]
        cmake_call += ["-DODE_ADD_BENCHMARK_SOURCE=OFF"]

    if args.ode_assertions:
        cmake_call += ["-DODE_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_call += ["-DODE_ENABLE_ASSERTIONS=OFF"]

    if args.cmake_generator == "Ninja":
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]

    if data.build.stdlib and not args.build_llvm:
        cmake_call += ["-DODE_STDLIB={}".format(data.build.stdlib)]

    if args.optimization_level:
        cmake_call += [
            "-DODE_OPTIMIZATION_LEVEL={}".format(args.optimization_level)
        ]

    if args.enable_gcov:
        cmake_call += ["-DODE_ENABLE_GCOV=ON"]
        cmake_call += ["-DCMAKE_BUILD_TYPE=Coverage"]
        cmake_call += ["-DODE_COVERAGE_MARK={}".format(COVERAGE_TARGET_MARK)]
    else:
        cmake_call += ["-DODE_ENABLE_GCOV=OFF"]
        if is_ode:
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.ode_build_variant)]
        else:
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.anthem_build_variant)]

    if args.std_clock:
        cmake_call += ["-DODE_STD_CLOCK=ON"]
    else:
        cmake_call += ["-DODE_STD_CLOCK=OFF"]

    if args.log_tests and test:
        cmake_call += ["-DODE_TEST_USE_NULL_SINK=OFF"]
    else:
        cmake_call += ["-DODE_TEST_USE_NULL_SINK=ON"]

    if args.multithreading:
        cmake_call += ["-DODE_MULTITHREADING=ON"]
    else:
        cmake_call += ["-DODE_MULTITHREADING=OFF"]

    if args.rpath:
        cmake_call += ["-DODE_RPATH={}".format(args.rpath)]

    if data.build.lua_in_source:
        cmake_call += ["-DODE_ADD_LUA_SOURCE=ON"]
    else:
        cmake_call += ["-DODE_ADD_LUA_SOURCE=OFF"]

    if test and platform.system() != "Windows":
        cmake_call += ["-DODE_ADD_GTEST_SOURCE=ON"]
    else:
        cmake_call += ["-DODE_ADD_GTEST_SOURCE=OFF"]

    if args.link_libcxx:
        cmake_call += ["-DODE_LINK_LIBCXX=ON"]
    else:
        cmake_call += ["-DODE_LINK_LIBCXX=OFF"]

    if args.build_llvm:
        cmake_call += ["-DODE_LINK_LIBCXX=ON"]
        cmake_call += ["-DODE_USE_LOCAL_LLVM=ON"]
        cmake_call += ["-DODE_STDLIB=libc++"]
    else:
        cmake_call += ["-DODE_USE_LOCAL_LLVM=OFF"]

    if test and platform.system() == "Windows":
        cmake_call += ["-DCMAKE_CXX_FLAGS=\
            \"/D_SILENCE_TR1_NAMESPACE_DEPRECATION_WARNING \
            /D_SILENCE_CXX17_OLD_ALLOCATOR_MEMBERS_DEPRECATION_WARNING\""]

    if args.extra_cmake_options:
        cmake_call += args.extra_cmake_options

    return cmake_call
