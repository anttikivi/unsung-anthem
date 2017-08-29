#===------------------------- invocation.py -------------------*- python -*-===#
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

import sys

from . import defaults, diagnostics, migration, shell


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
    if not (args.std == "c++latest"
            or args.std == "c++2a" or args.std == "c++17"
            or args.std == "c++14"):
        exit_rejecting_arguments(
            "C++ standard version is set to an invalid value: "
            + str(args.std))

    if args.stdlib_set:
        if not (args.stdlib == "libc++" or args.stdlib == "libstdc++"):
            exit_rejecting_arguments(
                "C++ standard library implementation is set to an invalid "
                "value: " + str(args.stdlib))

    if not (args.cmake_generator == "Ninja"
            or not args.cmake_generator == "Unix Makefiles"
            or not args.cmake_generator == "Xcode"
            or not args.cmake_generator == "Visual Studio 14 2015"
            or not args.cmake_generator == "Visual Studio 15 2017"
            or not args.cmake_generator == "Eclipse CDT4 - Ninja"):
        exit_rejecting_arguments('CMake generator is set to an invalid value: '
                                 + str(args.cmake_generator))

    if not (args.main_tool == "llvm"
            or not args.main_tool == "gcc"
            or not args.main_tool == "msbuild"):
        exit_rejecting_arguments(
            "The main tool is set to an invalid value: "
            + str(args.main_tool))

    if args.build_llvm and args.build_gcc:
        exit_rejecting_arguments(
            "Both LLVM and GCC cannot be built at the same time")

    if args.build_llvm and args.build_libcxx:
        exit_rejecting_arguments(
            "Both LLVM and libc++ cannot be built at the same time")

    if args.sdl and args.glfw:
        exit_rejecting_arguments(
            "Both SDL and GLFW cannot be used at the same time")


def set_up(parser):
    args = migration.parse_args(parser, sys.argv[1:])

    # Set the dry run setting of the shell utilities.
    shell.DRY_RUN = args.dry_run

    diagnostics.note("The main tool is set to {}".format(args.main_tool))
    diagnostics.note(
        "The main tool version is set to {}".format(args.main_tool_version))

    defaults.fix_main_tool(args)
    defaults.main_args(args)
    defaults.cxx_std(args)
    defaults.default_versions(args)
    defaults.file_arguments(args)

    validate_arguments(args)

    return args
