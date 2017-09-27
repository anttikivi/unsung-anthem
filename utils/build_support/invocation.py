#===------------------------- invocation.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for setting up the build
invocation.
"""


from __future__ import print_function

import os
import platform
import sys
import time

from . import \
    checkout, config, defaults, diagnostics, migration, reflection, shell

from .config import PRODUCT_CONFIG

from .mapping import Mapping

from .products import anthem

from .products.product import copy_build

from .toolchain import host_toolchain, set_arguments_to_toolchain

from .variables import ANTHEM_BUILD_ROOT, ANTHEM_SOURCE_ROOT


def exit_rejecting_arguments(message, parser=None):
    """
    Prints an error message and terminates the program with the same error exit
    code as an 'argparse' error would. Optionally prints the program usage
    before exiting if the parser is provided.

    This function is not pure as it prints command line output and terminates
    the program.

    message -- the error message.
    parser -- a ArgumentParser whose usage is printed.
    """
    print(message, file=sys.stderr)
    if parser:
        parser.print_usage(sys.stderr)
    sys.exit(2)  # 2 is the same as 'argparse' error exit code.


def validate_arguments(args):
    """
    Check that the command line arguments are valid.

    args -- the command line arguments.
    """
    if not (args.std == "c++latest"
            or args.std == "c++2a" or args.std == "c++17"
            or args.std == "c++14"):
        exit_rejecting_arguments(
            "C++ standard version is set to an invalid value: "
            + str(args.std))

    if args.stdlib:
        if not (args.stdlib == "libc++" or args.stdlib == "libstdc++"):
            exit_rejecting_arguments(
                "C++ standard library implementation is set to an invalid "
                "value: " + str(args.stdlib))

    if not (args.cmake_generator == "Ninja"
            or args.cmake_generator == "Unix Makefiles"
            or args.cmake_generator == "Xcode"
            or args.cmake_generator == "Visual Studio 14 2015"
            or args.cmake_generator == "Visual Studio 15 2017"
            or args.cmake_generator == "Eclipse CDT4 - Ninja"):
        exit_rejecting_arguments('CMake generator is set to an invalid value: '
                                 + str(args.cmake_generator))

    if not (args.main_tool == "llvm"
            or args.main_tool == "gcc"
            or args.main_tool == "msbuild"):
        exit_rejecting_arguments(
            "The main tool is set to an invalid value: "
            + str(args.main_tool))

    if args.build_llvm and args.build_libcxx:
        exit_rejecting_arguments(
            "Both LLVM and libc++ cannot be built at the same time")


def clean_delay():
    """
    Provide a short delay so accidentally invoked clean builds can be
    cancelled.
    """
    def _impl_write(index):
        sys.stdout.write(
            diagnostics.WARNING + "\b{!s}".format(index) + diagnostics.ENDC)
        sys.stdout.flush()
        time.sleep(1)
        return index

    sys.stdout.write(
        diagnostics.WARNING + "Starting a clean build in  "
        + diagnostics.ENDC)

    index_list = [_impl_write(i) for i in reversed(range(0, 4))]

    print(diagnostics.WARNING + "\b\b\b\bnow." + diagnostics.ENDC)

    return index_list


def set_up(parser):
    """
    Construct the build data and download the dependencies.

    parser -- the command line argument parser.
    """
    args = migration.parse_args(parser, sys.argv[1:])
    shell.DRY_RUN = args.dry_run
    diagnostics.note("The main tool is set to {}".format(args.main_tool))
    diagnostics.note(
        "The main tool version is set to {}".format(args.main_tool_version)
    )
    defaults.fix_main_tool(args)
    defaults.fix_threading(args)
    defaults.main_args(args)
    defaults.cxx_std(args)
    defaults.default_versions(args)
    defaults.file_arguments(args)
    defaults.authorization(args)
    validate_arguments(args)

    build_data = Mapping(
        args=args,
        source_root=ANTHEM_SOURCE_ROOT,
        build_root=os.path.join(ANTHEM_BUILD_ROOT, args.build_subdir),
        shared_build_root=os.path.join(
            ANTHEM_BUILD_ROOT, args.shared_build_subdir),
        install_root=os.path.join(ANTHEM_BUILD_ROOT, args.install_prefix),
        products=PRODUCT_CONFIG,
        host_target=args.host_target,
        std=args.std,
        stdlib=args.stdlib
    )

    config.apply_versions(build_data=build_data)

    if build_data.args.clean:
        clean_delay()
        shell.rmtree(path=build_data.build_root)
        shell.rmtree(path=build_data.shared_build_root, ignore_errors=True)

    shell.makedirs(build_data.build_root)
    shell.makedirs(build_data.shared_build_root)
    shell.makedirs(build_data.install_root)

    os.environ["TOOLCHAINS"] = build_data.args.darwin_xcrun_toolchain
    build_data.toolchain = host_toolchain(
        args=build_data.args,
        xcrun_toolchain=build_data.args.darwin_xcrun_toolchain)

    set_arguments_to_toolchain(
        args=build_data.args, toolchain=build_data.toolchain)

    defaults.skip_repositories(
        args=build_data.args, toolchain=build_data.toolchain)

    if build_data.args.ci:
        build_data["github_token"] = str(os.environ['ANTHEM_OAUTH'])
    else:
        build_data["github_token"] = args.auth_token

    build_data.connection_protocol = config.PROTOCOL

    if not args.build_only and not args.test_only and not args.docs_only:
        checkout.update(build_data=build_data)

    return build_data


def _build_tools(build_data):
    args = build_data.args
    toolchain = build_data.toolchain
    build_data["tools"] = Mapping()
    build_data["tools"]["set_up"] = list()
    build_tools = \
        not args.test_only and not args.docs_only and not args.run_only

    ninja_build_required = \
        args.build_ninja or \
        ((args.cmake_generator == "Ninja" or args.cmake_generator == "Xcode")
         and toolchain.ninja is None)
    cmake_build_required = args.build_cmake or (toolchain.cmake is None)
    llvm_build_required = args.build_llvm or args.build_libcxx

    if ninja_build_required:
        build_data.tools.set_up += ["ninja"]
    if cmake_build_required:
        build_data.tools.set_up += ["cmake"]
    if llvm_build_required:
        build_data.tools.set_up += ["llvm"]

    if build_tools:
        for tool in build_data.tools.set_up:
            product = build_data.products[tool]
            reflection.product_call(product, "set_up", build_data=build_data)
            diagnostics.debug_ok("{} is now built".format(product.repr))
    else:
        for tool in build_data.tools.set_up:
            product = build_data.products[tool]
            reflection.product_call(
                product, "set_toolchain", build_data=build_data)
            diagnostics.debug_ok("{} is now set into the toolchain".format(
                product.repr))


def _build_dependencies(build_data):
    args = build_data.args
    build_tools = not args.test_only and not args.docs_only
    build_dependencies = build_tools and not args.build_only
    build_catch = args.clion \
        or (args.build_test and not args.build_only and not args.test_only
            and not args.docs_only and not args.run_only)
    build_data["dependencies"] = Mapping()
    build_data["dependencies"]["build"] = list()

    if build_dependencies:
        build_data.dependencies.build += ["spdlog"]
        build_data.dependencies.build += ["args"]
        build_data.dependencies.build += ["glad"]
        build_data.dependencies.build += ["glfw"]
    if build_catch:
        build_data.dependencies.build += ["catch"]

    for dependency in build_data.dependencies.build:
        product = build_data.products[dependency]
        diagnostics.trace("Entering the build of {}".format(product.repr))
        if not reflection.product_exists(product) \
                or not reflection.product_function_exists(
                        product=product, function="build"):
            diagnostics.trace(
                "The product package of {} either doesn't exists or doesn't "
                "contain function 'build'".format(product.repr)
            )
            diagnostics.trace(
                "Thus, {} will be built using the default copy "
                "function".format(product.repr)
            )
            copy_build(
                build_data=build_data, product=product,
                subdir=product.build_subdir
            )
        else:
            reflection.product_call(
                build_data.products[dependency], "build", build_data=build_data
            )
        diagnostics.debug_ok("{} is now built".format(product.repr))


def invoke(build_data):
    """
    Perform the builds of the products and run the tests.

    build_data -- the build data.
    """
    args = build_data.args
    toolchain = build_data.toolchain

    _build_tools(build_data=build_data)

    if args.main_tool == "msbuild":
        if not toolchain.cc:
            toolchain.cc = toolchain.msbuild
        if not toolchain.cxx:
            toolchain.cxx = toolchain.msbuild

    diagnostics.note(
        "The executable name is set to {}".format(
            str(build_data.args.executable_name)
        )
    )
    diagnostics.note(
        "The test executable name is set to {}".format(
            str(build_data.args.test_executable_name)
        )
    )

    diagnostics.note("The host C compiler is set to {}".format(
        str(build_data.toolchain.cc)
    ))
    diagnostics.note("The host C++ compiler is set to {}".format(
        str(build_data.toolchain.cxx)
    ))
    diagnostics.note("Make is set to {}".format(
        str(build_data.toolchain.make)
    ))
    diagnostics.note("MSBuild is set to {}".format(
        str(build_data.toolchain.msbuild)
    ))
    diagnostics.note("Ninja is set to {}".format(
        str(build_data.toolchain.ninja)
    ))
    diagnostics.note("CMake is set to {}".format(
        str(build_data.toolchain.cmake)
    ))
    diagnostics.note("git is set to {}".format(
        str(build_data.toolchain.git)
    ))

    diagnostics.note("The C++ standard version is {}".format(build_data.std))

    if build_data.stdlib:
        diagnostics.note(
            "The C++ standard library is {}".format(build_data.stdlib)
        )

    if args.clion:
        diagnostics.note(
            "The CLion set-up is enabled and, thus, the final {} executable "
            "won't be built".format(build_data.products.anthem.repr)
        )

    _build_dependencies(build_data=build_data)

    build_anthem = \
        not args.install_only and not args.test_only and not args.docs_only \
        and not args.run_only

    if build_anthem:
        anthem.build(build_data=build_data, tests=False)

    build_tests = \
        args.build_test and not args.install_only and not args.test_only \
        and not args.docs_only and not args.run_only

    if build_tests:
        anthem.build(build_data=build_data, tests=True)

    run_tests = \
        (args.test or args.test_only) and not args.build_only \
        and not args.install_only and not args.docs_only and not args.run_only

    if run_tests:
        if platform.system() == "Windows":
            tests_build_dir = os.path.join(
                anthem.anthem_build_dir(build_data=build_data, tests=True),
                build_data.args.anthem_build_variant
            )
        else:
            tests_build_dir = anthem.anthem_build_dir(
                build_data=build_data, tests=True
            )
        with shell.pushd(tests_build_dir):
            if platform.system() == "Windows":
                test_executable = os.path.join(
                    tests_build_dir, args.test_executable_name + ".exe")
            else:
                test_executable = os.path.join(
                    tests_build_dir, args.test_executable_name)
            shell.call_without_sleeping([test_executable], echo=True)

    run = \
        (args.run or args.run_only) and not args.build_only \
        and not args.install_only and not args.docs_only

    if run:
        if platform.system() == "Windows":
            build_dir = os.path.join(
                anthem.anthem_build_dir(build_data=build_data, tests=False),
                build_data.args.anthem_build_variant
            )
        else:
            build_dir = anthem.anthem_build_dir(
                build_data=build_data, tests=False
            )
        with shell.pushd(build_dir):
            if platform.system() == "Windows":
                executable = os.path.join(
                    build_dir, args.executable_name + ".exe")
            else:
                executable = os.path.join(
                    build_dir, args.executable_name)
            shell.call_without_sleeping([executable], echo=True)

    return 0
