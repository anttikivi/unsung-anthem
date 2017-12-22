#===--------------------------- script.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing script-related helpers.
"""


import os
import platform
import sys

from .variables import HOME, ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME


def preset_files(args):
    """
    Get the files from which the program looks the presets up.

    args -- the parsed arguments of the program in preset mode.
    """

    if not args.preset_file_names:
        ret = [
            os.path.join(HOME, ".anthem-build-presets"),
            os.path.join(
                ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME, "utils",
                "build-presets.ini"
            )
        ]
    else:
        ret = args.preset_file_names
    return ret


def get_new_invocation(args, preset_args):
    """
    Create the call for the actual build script invocation from the presets.

    args -- the command line arguments.
    preset_args -- the parsed preset arguments.
    """
    def _impl_exec():
        return [(sys.executable
                 if platform.system() == "Windows" else None), sys.argv[0]]

    return list(filter(None, list(
        _impl_exec() + [
            "--from-preset",
            ("--dry-run" if args.dry_run else None),
            ("--clean" if args.clean else None)
        ]
        + preset_args)))
