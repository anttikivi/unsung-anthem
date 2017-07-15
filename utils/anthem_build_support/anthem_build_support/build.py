# anthem_build_support/build.py ----------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

from products import (anthem, cat, catch, clang, cmake, glfw, libcxx, llvm,
                      ninja, spdlog, test)


def build_cmake(args, toolchain, workspace):
    # Build CMake.
    cmake.build(args=args, toolchain=toolchain, workspace=workspace)


def build_llvm(args, toolchain, workspace):
    # Build LLVM and Clang.
    clang.build(args=args, toolchain=toolchain, workspace=workspace)
    libcxx.build(args=args, toolchain=toolchain, workspace=workspace)
    llvm.build(args=args, toolchain=toolchain, workspace=workspace)


def bazel_build(args, toolchain, workspace):
    """
    Executes the build of Unsung Anthem and its dependencies using Bazel.
    """

    # Set up the dependencies for the Bazel build.

    glfw.bazel(args=args, toolchain=toolchain, workspace=workspace)
    catch.bazel(args=args, toolchain=toolchain, workspace=workspace)
    spdlog.bazel(args=args, toolchain=toolchain, workspace=workspace)
    # cat.bazel(args=args, toolchain=toolchain, workspace=workspace)

    if 'Ninja' == args.cmake_generator:
        ninja.bazel(args=args, toolchain=toolchain, workspace=workspace)

    # Build Unsung Anthem.
    anthem.bazel(args=args, toolchain=toolchain, workspace=workspace)

    # TODO Build tests.
    # test.build(args=args, toolchain=toolchain, workspace=workspace)


def cmake_build(args, toolchain, workspace):
    """
    Executes the build of Unsung Anthem and its dependencies CMake.
    """

    # Start by building the dependencies of Unsung Anthem.

    # Build GLFW.
    glfw.build(args=args, toolchain=toolchain, workspace=workspace)

    # Build Catch.
    catch.build(args=args, toolchain=toolchain, workspace=workspace)

    # Build spdlog.
    spdlog.build(args=args, toolchain=toolchain, workspace=workspace)

    # Build cat.
    cat.build(args=args, toolchain=toolchain, workspace=workspace)

    # Build Unsung Anthem.
    anthem.build(args=args, toolchain=toolchain, workspace=workspace)

    # Build tests.
    if args.build_test:
        test.build(args=args, toolchain=toolchain, workspace=workspace)
