#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for Unsung Anthem build."""


from products.common import final


def anthem_build_dir(lib=False, test=False):
    """
    Create the directory name for the full build subdirectory of Unsung Anthem.
    """
    return final.build.anthem_build_dir(lib=lib, test=test)


def do_build(lib=False, test=False):
    """Build Unsung Anthem."""
    final.build.do_build(is_ode=False, lib=lib, test=test)


def should_build():
    """Check whether this product should be built."""
    return False
