#===--------------------------- shell.py ----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing shell helpers.
"""


from __future__ import print_function

import os
import pipes
import platform
import subprocess
import sys

from . import diagnostics


DRY_RUN = False


def _coerce_dry_run(dry_run_override):
    if dry_run_override is None:
        return DRY_RUN

    return dry_run_override


def quote(arg):
    """
    Quote single argument of command for passing to a shell.

    arg -- the argument to be quoted.
    """
    return pipes.quote(str(arg))


def quote_command(args):
    """
    Quote the command for passing to a shell.

    args -- the command to be quoted.
    """
    return " ".join([quote(a) for a in args])


def echo_command(dry_run, command, env=None, prompt="+ ", separate_env=False):
    """
    Print a command.

    dry_run -- whether or not dry run is enabled.
    command -- the command to be printed.
    env -- custom environment variables of the command.
    prompt -- the prompt to be printed before the command.
    separate_env -- whether or not the environment information is separated
    from the command by newlines.
    """
    def _env():
        return ["env"] + [quote(
            "{}={}".format(k, v)) for k, v in sorted(env.items())]

    def _env_separator():
        return "\n\n"

    def _command():
        return [quote(arg) for arg in command]

    if separate_env:
        output = [_env(), _env_separator()] + _command()
    else:
        output = _command()

    output_file = sys.stdout if dry_run else sys.stderr
    print(prompt + " ".join(output), file=output_file)
    file.flush()
    return command


def call(command, stderr=None, env=None, dry_run=None, echo=True):
    """
    Execute the given command. This function will raise an exception on any
    command failure.

    command -- the command to be run.
    stderr -- stderr to be passed to the subprocess.
    env -- custom environment variables of the command.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """

    def _env():
        ret = os.environ
        ret.update(env)
        return ret

    is_dry_run = _coerce_dry_run(dry_run)

    if is_dry_run or echo:
        echo_command(is_dry_run, command, env=env)

    if is_dry_run:
        return

    try:
        subprocess.check_call(command, env=_env(), stderr=stderr)
    except subprocess.CalledProcessError as err:
        diagnostics.fatal(
            "command terminated with a non-zero exit status "
            + str(err.returncode) + ", aborting")
    except OSError as err:
        diagnostics.fatal(
            "could not execute '" + quote_command(command)
            + "': " + err.strerror)


def call_without_sleeping(command, env=None, dry_run=False, echo=False):
    """
    Execute a command during which system sleep is disabled.
    By default, this ignores the state of the 'shell.dry_run' flag.

    command -- the command to be run.
    env -- custom environment variables of the command.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """

    # Disable system sleep, if possible.
    if platform.system == "Darwin":
        call_command = ["caffeinate"] + list(command)
    else:
        call_command = command

    call(call_command, env=env, dry_run=dry_run, echo=echo)
