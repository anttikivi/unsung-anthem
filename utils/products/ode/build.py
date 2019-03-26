#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

"""The support module containing the utilities for Obliging Ode build."""


from build_utils import reflection


def ode_build_dir(lib=False, test=False):
    """
    Create the directory name for the full build subdirectory of Obliging Ode.
    """
    return reflection.anthem_common_build_call(
        "ode_build_dir", lib=lib, test=test)


def do_build(lib=False, test=False):
    """Build Obliging Ode."""
    reflection.anthem_common_build_call(
        "do_build", is_ode=True, lib=lib, test=test)


def should_build():
    """Check whether this product should be built."""
    return False
