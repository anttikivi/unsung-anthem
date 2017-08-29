#===-------------------------- toolchain.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the toolchain helpers.
"""


import platform

from functools import partial

from . import diagnostics, xcrun

from .mapping import Mapping

from .which import which


def register_tools(args):
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
    tool_mapping = Mapping()
    for key, name in tools.items():
        diagnostics.debug("Looking for {}".format(name))
        found = func(cmd=name)
        diagnostics.debug_ok("Found {}".format(found))
        tool_mapping[key] = found
    return tool_mapping


def mac_os(tools, sdk, toolchain):
    # NOTE: xcrun searches from developer tools directory *and* from PATH.
    # Relatively slow, but 'which' is not necessary for Darwin.
    return find_tools(
        tools=tools, func=partial(xcrun.find, sdk=sdk, toolchain=toolchain))


def unix(tools):
    return find_tools(tools=tools, func=which)


def linux(tools):
    return unix(tools)


def free_bsd(tools):
    return unix(tools)


def cygwin(tools):
    return unix(tools)


def windows(tools):
    def _find(cmd):
        found = which(cmd)
        if found is not None:
            return found.replace('/c/', 'C:\\').replace('/', '\\')
        return found
    return find_tools(tools=tools, func=_find)


def host_toolchain(args, xcrun_toolchain="default"):
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
    else:
        raise NotImplementedError(
            "The platform '{}' does not have a defined "
            "toolchain.".format(sys))
