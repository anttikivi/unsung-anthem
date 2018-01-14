#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


"""
The support module containing the utilities for builds.
"""


import os

from build_utils import diagnostics, workspace

from script_support import data


def check_source(key, subproject=None, name=None):
    """
    Check if the source directory of the product exists.

    key -- the name of the product.
    subproject -- a possible subproduct of the product for which the path is
    checked.
    name -- a custom name of the source directory.
    """
    product = data.build.products[key]
    if subproject:
        source_dir = workspace.source_dir(
            product=product, subproduct=subproject
        )
        if not os.path.exists(source_dir):
            diagnostics.fatal(
                "Cannot find source directory for {} ({}) (tried {})".format(
                    subproject, product.repr, source_dir
                )
            )
    elif name:
        source_dir = workspace.source_dir(product=product, name=name)
        if not os.path.exists(source_dir):
            diagnostics.fatal(
                "Cannot find source directory for {} (tried {})".format(
                    product.repr, source_dir
                )
            )
    else:
        source_dir = workspace.source_dir(product)
        if not os.path.exists(source_dir):
            diagnostics.fatal(
                "Cannot find source directory for {} (tried {})".format(
                    product.repr, source_dir
                )
            )


def binary_exists(product, path, target=None, subproject=None):
    """
    Check if the binary for the product exists.

    product -- the product.
    path -- the path to the binary.
    target -- a custom target of the product.
    subproject -- a possible subproject which should be checked instead.
    """
    build_dir = workspace.build_dir(
        target=target,
        product=product,
        subproject=subproject)
    if os.path.exists(path) and os.path.exists(build_dir):
        if subproject:
            diagnostics.debug_note(
                "{} ({}) is already built and should not be re-built".format(
                    subproject, product.repr
                )
            )
        else:
            diagnostics.debug_note(
                "{} is already built and should not be re-built".format(
                    product.repr
                )
            )
        return True
    return False
