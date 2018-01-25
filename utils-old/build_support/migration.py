#===------------------------- migration.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing helpers for parsing the command line arguments.
"""


def parse_args(parser, argv):
    """
    Parse given argument list with given argparse.ArgumentParser.

    Return a processed arguments object. Any unknown arguments are stored in
    'build_script_impl_args' attribute as a list. Ignores '--' to be
    compatible with old style argument list.

    parser -- the parser containing the information about the command line
    options.
    argv -- the command line arguments.
    """
    args, unknown_args = parser.parse_known_args(
        list(arg for arg in argv if arg != '--'))
    args.build_script_impl_args = unknown_args
    return args
