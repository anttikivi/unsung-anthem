# anthem_build_support/call.py -----------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

import platform
from . import shell


def call_without_sleeping(command, env=None, dry_run=False, echo=False):
    """
    Execute a command during which system sleep is disabled.
    By default, this ignores the state of the `shell.dry_run` flag.
    """

    # Disable system sleep, if possible.
    if platform.system() == 'Darwin':
        # Don't mutate the caller's copy of the arguments.
        call_command = ["caffeinate"] + list(command)
    else:
        call_command = command

    shell.call(call_command, env=env, dry_run=dry_run, echo=echo)
