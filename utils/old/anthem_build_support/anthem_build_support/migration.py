# anthem_build_support/migration.py ------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


def parse_args(parser, argv):
    """
    Parse given argument list with given argparse.ArgumentParser.

    Return a processed arguments object. Any unknown arguments are stored in
    `build_script_impl_args` attribute as a list.
    Ignores '--' to be compatible with old style argument list.

        build-script -RT -- --reconfigure
    """
    args, unknown_args = parser.parse_known_args(
        list(arg for arg in argv if arg != '--'))
    args.build_script_impl_args = unknown_args
    return args
