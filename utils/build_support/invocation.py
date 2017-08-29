#===------------------------- invocation.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for setting up the build
invocation.
"""


import sys

from . import defaults, diagnostics, migration, shell


def set_up(parser):
    args = migration.parse_args(parser, sys.argv[1:])

    # Set the dry run setting of the shell utilities.
    shell.DRY_RUN = args.dry_run

    diagnostics.note("The main tool is set to {}".format(args.main_tool))
    diagnostics.note(
        "The main tool version is set to {}".format(args.main_tool_version))

    defaults.fix_main_tool(args)

    defaults.main_args(args)

    defaults.cxx_std(args)

    defaults.default_versions(args)

    return args
