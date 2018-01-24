#===--------------------------- xcrun.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
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

    for product in data.build.products:
        if product.check_if_tool() \
                and reflection.get_product_build_call(product, "should_build"):
            diagnostics.trace("Entering the build of {}".format(product.repr))
            reflection.product_build_call(product, "do_build")
            diagnostics.debug_ok("{} is now built".format(product.repr))

    if args.main_tool == "msbuild":
        if not toolchain.cc:
            toolchain.cc = toolchain.msbuild
        if not toolchain.cxx:
            toolchain.cxx = toolchain.msbuild

    diagnostics.note(
        "The executable name is set to {}".format(str(args.executable_name))
    )
    diagnostics.note(
        "The test executable name is set to {}".format(
            str(args.test_executable_name)
        )
    )

    diagnostics.note("The host C compiler is set to {}".format(
        str(toolchain.cc)
    ))
    diagnostics.note("The host C++ compiler is set to {}".format(
        str(toolchain.cxx)
    ))
    diagnostics.note("Make is set to {}".format(str(toolchain.make)))
    diagnostics.note("MSBuild is set to {}".format(str(toolchain.msbuild)))
    diagnostics.note("Ninja is set to {}".format(str(toolchain.ninja)))
    diagnostics.note("CMake is set to {}".format(str(toolchain.cmake)))
    diagnostics.note("git is set to {}".format(str(toolchain.git)))

    diagnostics.note("The C++ standard version is {}".format(data.build.std))

    if data.build.stdlib:
        diagnostics.note(
            "The C++ standard library is {}".format(data.build.stdlib)
        )
