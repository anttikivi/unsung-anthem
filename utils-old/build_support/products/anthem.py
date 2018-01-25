#===--------------------------- anthem.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the Unsung Anthem product helpers.
"""


import os
import platform

from . import sdl

from .product import check_source

from .. import config, diagnostics, shell, workspace

from ..variables import ANTHEM_REPO_NAME


def anthem_build_dir(build_data, tests=False):
    """
    Create the directory name for the full build subdirectory of Unsung Anthem.

    build_data -- the build data.
    tests -- whether or not the directory name should be created for the tests
    binaries.
    """
    product = build_data.products.anthem
    if tests:
        return os.path.join(
            build_data.build_root, "{}-{}-{}".format(
                product.identifier, "test", build_data.host_target
            )
        )
    # elif lib:
    #     return os.path.join(
    #         build_data.build_root, "{}-{}-{}".format(
    #             product.identifier, "lib", build_data.host_target
    #         )
    #     )
    return os.path.join(
        build_data.build_root,
        "{}-{}".format(product.identifier, build_data.host_target)
    )


def construct_cmake_call(build_data, tests=False, clion=False):
    """
    """
    product = build_data.products.anthem
    args = build_data.args
    toolchain = build_data.toolchain
    source_dir = workspace.source_dir(product=product, name=ANTHEM_REPO_NAME)

    if not clion:
        cmake_call = [
            toolchain.cmake,
            source_dir,
            "-G", args.cmake_generator
        ]
    else:
        cmake_call = []

    if platform.system() == "Windows":
        install_root = build_data.install_root.replace("\\", "/")
    else:
        install_root = build_data.install_root

    cmake_call += [
        "-DANTHEM_INSTALL_PREFIX={}".format(install_root),
        "-DANTHEM_CXX_VERSION={}".format(build_data.std),
        "-DANTHEM_EXECUTABLE_NAME={}".format(args.executable_name),
        "-DANTHEM_LIB_NAME={}".format(args.lib_name),
        "-DANTHEM_TEST_EXECUTABLE_NAME={}".format(args.test_executable_name),
        "-DANTHEM_MAIN_COMPILER_TOOL={}".format(args.main_tool),
        "-DANTHEM_LOGGER_NAME={}".format(product.logger_name),
        "-DANTHEM_INPUT_LOGGER_NAME={}-{}".format(
            product.logger_name, "input"),
        "-DANTHEM_OPENGL_VERSION_MAJOR={}".format(
            product.opengl.version.major),
        "-DANTHEM_OPENGL_VERSION_MINOR={}".format(
            product.opengl.version.minor),
        "-DANTHEM_WINDOW_NAME={}".format(product.window_name)
    ]

    cmake_call += ["-DANTHEM_SDL_VERSION={}".format(
        build_data.products.sdl.version)]

    if args.anthem_assertions:
        cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=ON"]
    else:
        cmake_call += ["-DANTHEM_ENABLE_ASSERTIONS=OFF"]

    if not tests:
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE={}".format(
            "clion" if args.clion else "anthem"
        )]
    else:
        cmake_call += ["-DANTHEM_EXECUTABLE_TYPE=test"]

    if args.cmake_generator == "Ninja":
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]

    if build_data.stdlib:
        cmake_call += ["-DANTHEM_STDLIB={}".format(build_data.stdlib)]

    if args.build_llvm or args.build_libcxx:
        cmake_call += ["-DCMAKE_CXX_FLAGS=-I{}/include/c++/v1".format(
            build_data.install_root)]
        cmake_call += ["-DANTHEM_LINK_CXXABI=ON"]

    if not clion:
        if args.enable_gcov:
            cmake_call += ["-DANTHEM_ENABLE_GCOV=ON"]
            cmake_call += ["-DCMAKE_BUILD_TYPE=Coverage"]
        else:
            cmake_call += ["-DANTHEM_ENABLE_GCOV=OFF"]
            cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(
                args.anthem_build_variant
            )]

    if args.threading == "multithread":
        cmake_call += ["-DANTHEM_MULTITHREADING=ON"]
    elif args.threading == "singlethread":
        cmake_call += ["-DANTHEM_MULTITHREADING=OFF"]

    cmake_call += args.extra_cmake_options

    return cmake_call


def build(build_data, tests=False):
    """
    Build Unsung Anthem.

    build_data -- the build data.
    tests -- whether or not the tests should be built rather than the actual
    executable.
    """
    args = build_data.args
    toolchain = build_data.toolchain
    product = build_data.products.anthem
    build_dir = anthem_build_dir(build_data=build_data, tests=tests)
    check_source(product=product, name=ANTHEM_REPO_NAME)
    shell.makedirs(build_dir)

    cmake_env = {"CC": str(toolchain.cc), "CXX": str(toolchain.cxx)}

    cmake_call = construct_cmake_call(
        build_data=build_data, tests=tests, clion=False)

    if not args.clion:
        with shell.pushd(build_dir):
            shell.call_without_sleeping(cmake_call, env=cmake_env, echo=True)
            if args.cmake_generator == "Ninja":
                shell.ninja(build_data=build_data)
            elif args.cmake_generator == "Unix Makefiles":
                shell.make(build_data=build_data)
                if args.enable_gcov and tests:
                    shell.make(
                        build_data=build_data,
                        target="{}_coverage".format(args.executable_name)
                    )
                    if args.ci:
                        shell.call([
                            "coveralls-lcov", "--repo-token",
                            os.environ["ANTHEM_COVERALLS_REPO_TOKEN"],
                            "{}_coverage.info.cleaned".format(
                                args.executable_name
                            )
                        ])

            elif args.visual_studio:
                msbuild_args = ["anthem.sln"]

                if args.msbuild_logger is not None:
                    msbuild_args += ["/logger:{}".format(
                        str(args.msbuild_logger)
                    )]

                msbuild_args += ["/p:Configuration={}".format(
                    args.anthem_build_variant
                )]

                if platform.system() == "Windows":
                    msbuild_args += ["/p:Platform=Win32"]

                shell.msbuild(build_data=build_data, args=msbuild_args)

    elif args.clion and not args.visual_studio:
        diagnostics.note(
            "CMake would be called with the following command and "
            "environment variables:"
        )
        shell.print_command(command=cmake_call, env=cmake_env)
        diagnostics.note(
            "Please copy the following environment variables to into your "
            "CLion settings:"
        )
        shell.print_env_fine(env=cmake_env)
        diagnostics.note(
            "Please copy the following CMake options to into your CLion "
            "settings:"
        )
        clion_cmake_options = construct_cmake_call(
            build_data=build_data, tests=tests, clion=True)
        shell.print_command_fine(command=clion_cmake_options)

    if args.visual_studio:
        sdl.copy_dynamic(build_data=build_data, dest=os.path.join(
            build_dir,
            args.anthem_build_variant))
