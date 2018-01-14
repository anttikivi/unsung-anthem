#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for LLVM build.
"""


from products import common

from script_support import data


def do_build():
    """
    Builds LLVM.
    """
    product = data.build.products.llvm

    common.build.check_source(key="llvm", subproject="llvm")
