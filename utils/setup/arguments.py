#===------------------------- arguments.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for setting up the build
arguments.
"""


from __future__ import print_function

from build_utils import shell, workspace


def set_default_args(args):
    """
    Construct the build data and download the dependencies.
    """
    if args.source_llvm:
        args.build_llvm = True

    shell.DRY_RUN = args.dry_run

    if args.build_subdir is None:
        args.build_subdir = workspace.compute_build_subdir(args)
