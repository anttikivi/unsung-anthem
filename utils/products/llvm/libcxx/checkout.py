#===-------------------------- checkout.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for libcxx checkout.
"""


import os

from build_utils import shell

from script_support.variables import ANTHEM_SOURCE_ROOT


def remove_bad_symlink(subdir):
    """
    Remove the bad symlink in libc++.

    subdir -- the name of the libc++ subdir in the release archive.
    """
    # FIXME: This is bad, this is hardcoded.
    shell.rm(os.path.join(
        ANTHEM_SOURCE_ROOT, "libcxx", "temp", subdir, "test", "std",
        "experimental", "filesystem", "Inputs", "static_test_env",
        "bad_symlink"
    ))
