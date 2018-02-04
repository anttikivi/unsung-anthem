#===------------------------------- tools.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for building the tools necessary
for the build.
"""


from build_utils import diagnostics, reflection

from script_support import data


def build_tools():
    """
    Builds the tools necessary for the build invocation.
    """
    args = data.build.args
    toolchain = data.build.toolchain

    for key, product in data.build.products.items():
        diagnostics.trace(
            "Checking if {} needs to be built".format(product.repr)
        )
        should_build = reflection.build_call(product, "should_build")
        only_anthem = not args.build_anthem and product.anthem_only
        if only_anthem:
            diagnostics.note(
                "{} is not built as it is only required by Unsung Anthem "
                "which is not built".format(product.repr)
            )
        if product.is_tool and should_build and not only_anthem:
            diagnostics.trace_head(
                "Entering the build of {}".format(product.repr)
            )
            reflection.build_call(product, "do_build")
            diagnostics.debug_ok("{} is now built".format(product.repr))
        elif product.is_tool and not should_build:
            diagnostics.trace("{} is not built".format(product.repr))

    if args.main_tool == "msbuild":
        if not toolchain.cc:
            toolchain.cc = toolchain.msbuild
        if not toolchain.cxx:
            toolchain.cxx = toolchain.msbuild

    diagnostics.fine("The Ode library name is set to {}".format(args.ode_name))
    diagnostics.fine(
        "The Ode test executable name is set to {}".format(args.ode_test_name)
    )

    diagnostics.fine("The Unsung Anthem executable name is set to {}".format(
        args.anthem_name
    ))
    diagnostics.fine("The Unsung Anthem library name is set to {}".format(
        args.anthem_lib_name
    ))
    diagnostics.fine(
        "The Unsung Anthem test executable name is set to {}".format(
            args.anthem_test_name
        )
    )

    diagnostics.fine("The host C compiler is set to {}".format(
        str(toolchain.cc)
    ))
    diagnostics.fine("The host C++ compiler is set to {}".format(
        str(toolchain.cxx)
    ))
    diagnostics.fine("Make is set to {}".format(str(toolchain.make)))
    diagnostics.fine("MSBuild is set to {}".format(str(toolchain.msbuild)))
    diagnostics.fine("Ninja is set to {}".format(str(toolchain.ninja)))
    diagnostics.fine("CMake is set to {}".format(str(toolchain.cmake)))
    diagnostics.fine("git is set to {}".format(str(toolchain.git)))

    diagnostics.fine("The C++ standard version is {}".format(data.build.std))

    if data.build.stdlib:
        diagnostics.fine(
            "The C++ standard library is {}".format(data.build.stdlib)
        )
