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


def quote(arg):
    def _impl():
        return pipes.quote(str(arg))

    return _impl()


def quote_command(args):
    """
    quote_command(args) -> str

    Quote the command for passing to a shell.
    """
    return " ".join([quote(a) for a in args])


def echo_command(dry_run, command, env=None, prompt="+ ", separate_env=False):
    def _impl_env():
        return (["env"] + [quote("%s=%s" % (k, v))
                           for (k, v) in sorted(env.items())]) \
            if env is not None else None

    def _impl_separate_env():
        return "\n\n" if separate_env else None

    def _impl_command():
        return [quote(arg) for arg in command]

    def _impl():
        output = filter(None, list([_impl_env(), _impl_separate_env()]
                                   + _impl_command()))
        output_file = sys.stdout if dry_run else sys.stderr
        print(prompt + " ".join(output), file=output_file)
        file.flush()
        return command

    return _impl()


def call(command, stderr=None, env=None, dry_run=None, echo=True):
    """
    call(command, ...) -> str

    Execute the given command.

    This function will raise an exception on any command failure.
    """
    def _impl_env():
        ret = os.environ
        # A bit of impurity.
        ret.update(env)
        return ret

    if dry_run or echo:
        echo_command(dry_run, command, env=env)
    if dry_run:
        return

    call_env = _impl_env()

    try:
        subprocess.check_call(command, env=call_env, stderr=stderr)
    except subprocess.CalledProcessError as err:
        diagnostics.fatal("command terminated with a non-zero exit status "
                          + str(err.returncode) + ", aborting")
    except OSError as err:
        diagnostics.fatal("could not execute '" + quote_command(command)
                          + "': " + err.strerror)


def call_without_sleeping(command, env=None, dry_run=False, echo=False):
    """
    Execute a command during which system sleep is disabled.
    By default, this ignores the state of the `shell.dry_run` flag.
    """

    # Disable system sleep, if possible.
    call_command = (["caffeinate"] + list(command)) \
        if platform.system == "Darwin" else command

    call(call_command, env=env, dry_run=dry_run, echo=echo)
