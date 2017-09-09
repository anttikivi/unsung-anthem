#===--------------------------- catch.py ----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the Catch product helpers.
"""


import os

from .product import binary_exists, check_source

from .. import shell, workspace


def build(build_data):
    """
    """
    product = build_data.products.catch
    check_source(product=product)
    bin_path = os.path.join(build_data.install_root, "include", "catch.hpp")
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    source_dir = workspace.source_dir(product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    if not workspace.is_include_dir_made(build_data=build_data) \
            and workspace.lib_file_exists(
                build_data=build_data, path="catch.hpp"):
        shell.rm(bin_path)
    shell.copy(os.path.join(build_dir, "catch.hpp"), bin_path)
