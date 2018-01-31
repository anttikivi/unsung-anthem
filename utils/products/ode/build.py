#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Ode build.
"""


from products.common import final


def ode_build_dir(lib=False, test=False):
    """
    Create the directory name for the full build subdirectory of Ode.

    lib -- whether or not the directory name should be created for the
    libraries binaries.
    test -- whether or not the directory name should be created for the tests
    binaries.
    """
    return final.build.ode_build_dir(lib=lib, test=test)


def do_build(lib=False, test=False):
    """
    Build Ode.

    lib -- whether or not the libraries should be built rather than the actual
    executable.
    test -- whether or not the tests should be built rather than the actual
    executable.
    """
    final.build.do_build(is_ode=True, lib=lib, test=test)


def should_build():
    """
    Check whether this product should be built.
    """
    return False