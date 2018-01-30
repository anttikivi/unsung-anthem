#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Catch2 build.
"""


import os

from build_utils import shell, workspace

from products import common

from script_support import data


def do_build():
    """
    Build Catch2.
    """
    product = data.build.products.catch2
    common.build.check_source(product.identifier)
    bin_path = os.path.join(data.build.local_root, "include", "catch.hpp")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    source_dir = workspace.source_dir(product)
    if not workspace.is_include_dir_made() \
            and workspace.lib_file_exists(path="catch.hpp"):
        shell.rm(bin_path)
    shell.copy(os.path.join(source_dir, "catch.hpp"), bin_path)


def should_build():
    """
    Check whether this product should be built.
    """
    return data.build.args.build_test
