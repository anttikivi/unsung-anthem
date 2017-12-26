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


import os
import sys
import time

from . import diagnostics, shell

from .variables import ANTHEM_SOURCE_ROOT, ANTHEM_BUILD_ROOT

from .toolchain import host_toolchain

from build_anthem import config

from build_anthem.config import PRODUCT_CONFIG

from build_utils.mapping import Mapping


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
        exit_rejecting_arguments("CMake generator is set to an invalid value: "
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


def set_up(args):
    """
    Construct the build data and download the dependencies.

    parser -- the command line argument parser.
    """
    shell.DRY_RUN = args.dry_run
    diagnostics.note("The main tool is set to {}".format(args.main_tool))
    diagnostics.note(
        "The main tool version is set to {}".format(args.main_tool_version)
    )
    validate_arguments(args)

    build_data = Mapping(
        args=args,
        source_root=ANTHEM_SOURCE_ROOT,
        build_root=os.path.join(ANTHEM_BUILD_ROOT, args.build_subdir),
        install_root=os.path.join(ANTHEM_BUILD_ROOT, args.install_prefix),
        products=PRODUCT_CONFIG
    )

    if build_data.args.clean:
        clean_delay()
        shell.rmtree(path=build_data.build_root)

    shell.makedirs(build_data.build_root)
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
        build_data["github_token"] = str(os.environ["ANTHEM_OAUTH"])
    else:
        build_data["github_token"] = args.auth_token

    build_data.connection_protocol = config.PROTOCOL

    checkout.update(build_data=build_data)

    return build_data
