#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

"""The support module containing the utilities for Clara build."""


import os

from build_utils import shell, workspace

from products import common

from script_support import data


def do_build():
    """Build Clara."""
    product = data.build.products.clara
    common.build.check_source(product)
    bin_path = os.path.join(data.build.local_root, "include", "clara.hpp")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    source_dir = workspace.source_dir(product)
    if not workspace.is_include_dir_made() and workspace.lib_file_exists(
            path="clara.hpp"):
        shell.rm(bin_path)
    shell.copy(os.path.join(source_dir, "clara.hpp"), bin_path)


def should_build():
    """
    Check whether this product should be built.
    """
    return True
