#===----------------------------- toolchain.py ---------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the toolchain helpers.
"""


import platform

from functools import partial

from script_support import data

from . import diagnostics, xcrun

from .mapping import Mapping

from .which import where, which


def register_tools(args):
    """
    Register the tools to the toolchain.

    args -- the command line argument dictionary.
    """
    tools = Mapping()
    sys = platform.system()
    if args.search_cc is not None:
        tools.cc = args.search_cc
    else:
        tools.cc = "clang-cl" if sys == "Windows" else "clang"
    if args.search_cxx is not None:
        tools.cxx = args.search_cxx
    else:
        tools.cxx = "clang-cl" if sys == "Windows" else "clang++"
    tools.msbuild = "msbuild"
    tools.ninja = "ninja"
    tools.cmake = "cmake"
    tools.git = "git"
    tools.make = "make"
    return tools


def find_tools(tools, func):
    """Find the executables of the given tools."""
    tool_mapping = Mapping()
    for key, name in tools.items():
        diagnostics.debug("Looking for {}".format(name))
        found = func(cmd=name)
        diagnostics.debug_ok("Found {}".format(found))
        tool_mapping[key] = found
    return tool_mapping


def mac_os(tools):
    """Find the tools in the toolchain on macOS."""
    # NOTE: xcrun searches from developer tools directory *and* from PATH.
    # Relatively slow, but 'which' is not necessary for Darwin.
    return find_tools(tools=tools, func=partial(xcrun.find))


def unix(tools):
    """Find the tools in the toolchain on a generic Unix system."""
    return find_tools(tools=tools, func=which)


def linux(tools):
    """Find the tools in the toolchain on Linux."""
    return unix(tools)


def free_bsd(tools):
    """Find the tools in the toolchain on FreeBSD."""
    return unix(tools)


def cygwin(tools):
    """Find the tools in the toolchain on Cygwin."""
    return unix(tools)


def windows(tools):
    """Find the tools in the toolchain on Windows."""
    def _find(cmd):
        found = where(cmd)
        if found is not None:
            return found.replace("/c/", "C:\\").replace("/", "\\")
        return found
    return find_tools(tools=tools, func=_find)


def host_toolchain(args):
    """Construct the toolchain for the current host platform."""
    tools = register_tools(args=args)
    sys = platform.system()
    if sys == "Darwin":
        return mac_os(tools=tools)
    elif sys == "Linux":
        return linux(tools=tools)
    elif sys == "FreeBSD":
        return free_bsd(tools=tools)
    elif sys.startswith("CYGWIN"):
        return cygwin(tools=tools)
    elif sys == "Windows":
        return windows(tools=tools)
    raise NotImplementedError(
        "The platform '{}' does not have a defined toolchain".format(sys))


def set_arguments_to_toolchain(args, toolchain):
    """
    Set the tools from the command line arguments to the toolchain if they are
    set on the command line.
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
    # if args.make is not None:
    #     toolchain.make = args.make
