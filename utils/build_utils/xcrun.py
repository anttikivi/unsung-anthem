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
def find(cmd, sdk=None, toolchain=None):
    """
    Return the path for the given tool, according to 'xcrun --find', using
    the given sdk and toolchain.

    If 'xcrun --find' cannot find the tool, return None.
    """
    command = ["xcrun", "--find", cmd]
    if sdk is not None:
        command += ["--sdk", sdk]
    if toolchain is not None:
        command += ["--toolchain", toolchain]

    # "xcrun --find" prints to stderr when it fails to find the given tool.
    # We swallow that output with a pipe.
    out = shell.capture(
        command,
        stderr=shell.DEVNULL,
        dry_run=False,
        echo=False,
        optional=True)
    if out is None:
        return None
    return out.rstrip()


@cache_util.cached
def sdk_path(sdk):
    """
    Return the path string for given SDK, according to
    'xcrun --show-sdk-path'.

    If 'xcrun --show-sdk-path' cannot find the SDK, return None.
    """
    command = ["xcrun", "--sdk", sdk, "--show-sdk-path"]
    out = shell.capture(command, dry_run=False, echo=False, optional=True)
    if out is None:
        return None
    return out.rstrip()
