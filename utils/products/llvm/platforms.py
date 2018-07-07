#===----------------------------- platform.py ---------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for LLVM platform."""


import platform

from build_utils import diagnostics

from script_support import data


def resolve():
    """Resolve the platform which is used in the LLVM filename."""
    product = data.build.products.llvm
    if platform.system() == "Linux":
        return "x86_64-linux-gnu-ubuntu-14.04"
    elif platform.system() == "Darwin":
        return "x86_64-apple-darwin"

    diagnostics.warn(
        "{} will not be downloaded as the platform is not supported".format(
            product.repr))
    return None
