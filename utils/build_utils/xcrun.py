#===------------------------------- xcrun.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the xcrun helpers.
"""


from __future__ import absolute_import

from . import cache_util, shell


@cache_util.cached
def find(cmd):
    """
    Return the path for the given tool, according to 'xcrun --find', using
    the given sdk and toolchain.

    If 'xcrun --find' cannot find the tool, return None.
    """
    command = [
        "xcrun", "--find", cmd, "--sdk", "macosx", "--toolchain", "default"
    ]
    # "xcrun --find" prints to stderr when it fails to find the given tool.
    # We swallow that output with a pipe.
    out = shell.capture(
        command, stderr=shell.DEVNULL, dry_run=False, echo=False,
        optional=True)
    if out is None:
        return None
    return out.rstrip()
