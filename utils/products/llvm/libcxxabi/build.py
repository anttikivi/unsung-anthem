#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for libc++abi build.
"""


import os

from build_utils import shell, workspace

from products import common

from script_support import data


def set_up():
    """
    Set up the libc++abi source for the build.
    """
    product = data.build.products.llvm
    key = product.subprojects["libcxxabi"]

    common.build.check_source(key=product.identifier, subproject=key)

    source_dir = workspace.source_dir(product=product, subproject=key)

    shell.rmtree(os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "projects",
        key
    ))
    shell.copytree(source_dir, os.path.join(
        workspace.source_dir(product=product, subproject=product.identifier),
        "projects",
        key
    ))
