#===------------------------- toolchain.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the toolchain helpers.
"""


import platform

from functools import partial

from build_utils import diagnostics, xcrun

from build_utils.mapping import Mapping

from build_utils.where import where

from build_utils.which import which


def register_tools(args):
    """
    Register the tools to the toolchain.

    args -- the command line argument dictionary.
    """
    tools = Mapping()
    sys = platform.system()
    if args.main_tool == "llvm":
        if sys == "Windows":
            tools.cc = "clang-cl"
            tools.cxx = "clang-cl"
        else:
            if args.main_tool_version == "default":
                tools.cc = "clang"
                tools.cxx = "clang++"
            else:
                tools.cc = "clang-{}".format(args.main_tool_version)
                tools.cxx = "clang++-{}".format(args.main_tool_version)
    elif args.main_tool == "gcc":
        if args.main_tool_version == "default":
            tools.cc = "gcc"
            tools.cxx = "g++"
        else:
            tools.cc = "gcc-{}".format(args.main_tool_version)
            tools.cxx = "g++-{}".format(args.main_tool_version)
    elif args.main_tool == "msbuild":
        tools.cc = "msbuild"
        tools.cxx = "msbuild"
    tools.msbuild = "msbuild"
    tools.ninja = "ninja"
    tools.cmake = "cmake"
    tools.git = "git"
    return tools


def find_tools(tools, func):
    """
    Find the executables of the given tools.

    tools -- the names of the tools to look for.
    func -- the function which is used for the lookup.
    """
    tool_mapping = Mapping()
    for key, name in tools.items():
        diagnostics.debug("Looking for {}".format(name))
        found = func(cmd=name)
        diagnostics.debug_ok("Found {}".format(found))
        tool_mapping[key] = found
    return tool_mapping


def mac_os(tools, sdk, toolchain):
    """
    Find the tools in the toolchain on macOS.

    tools -- the names of the tools to look for.
    sdk -- the name of the SDK.
    toolchain -- the toolchain object.
    """
    # NOTE: xcrun searches from developer tools directory *and* from PATH.
    # Relatively slow, but 'which' is not necessary for Darwin.
    return find_tools(tools=tools, func=partial(xcrun.find, sdk=sdk, toolchain=toolchain))
    # return find_tools(tools=tools, func=which)


def unix(tools):
    """
    Find the tools in the toolchain on a generic Unix system.

    tools -- the names of the tools to look for.
    """
    return find_tools(tools=tools, func=which)


def linux(tools):
    """
    Find the tools in the toolchain on Linux.

    tools -- the names of the tools to look for.
    """
    return unix(tools)


def free_bsd(tools):
    """
    Find the tools in the toolchain on FreeBSD.

    tools -- the names of the tools to look for.
    """
    return unix(tools)


def cygwin(tools):
    """
    Find the tools in the toolchain on Cygwin.

    tools -- the names of the tools to look for.
    """
    return unix(tools)


def windows(tools):
    """
    Find the tools in the toolchain on Windows.

    tools -- the names of the tools to look for.
    """
    def _find(cmd):
        found = where(cmd)
        if found is not None:
            return found.replace("/c/", "C:\\").replace("/", "\\")
        return found
    return find_tools(tools=tools, func=_find)


def host_toolchain(args, xcrun_toolchain="default"):
    """
    Construct the toolchain for the current host platform.

    args -- the command line argument dictionary.
    xcrun_toolchain -- the xcrun toolchain on macOS.
    """
    tools = register_tools(args=args)
    sys = platform.system()
    if sys == "Darwin":
        return mac_os(tools=tools, sdk="macosx", toolchain=xcrun_toolchain)
    elif sys == "Linux":
        return linux(tools=tools)
    elif sys == "FreeBSD":
        return free_bsd(tools=tools)
    elif sys.startswith("CYGWIN"):
        return cygwin(tools=tools)
    elif sys == "Windows":
        return windows(tools=tools)
    raise NotImplementedError(
        "The platform '{}' does not have a defined toolchain.".format(sys)
    )


def set_arguments_to_toolchain(args, toolchain):
    """
    Set the tools from the command line arguments to the toolchain if they are
    set on the command line.

    args -- the command line argument dictionary.
    toolchain -- the toolchain.
    """
    if args.host_cc is not None:
        toolchain.cc = args.host_cc
    if args.host_cxx is not None:
        toolchain.cxx = args.host_cxx
    if args.msbuild is not None:
        toolchain.msbuild = args.msbuild
    if args.cmake is not None:
        toolchain.cmake = args.cmake
    if args.git is not None:
        toolchain.git = args.git
