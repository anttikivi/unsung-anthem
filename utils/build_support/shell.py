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

import distutils
import os
import pipes
import platform
import shutil
import subprocess
import sys
import tarfile
import zipfile

from contextlib import contextmanager

from . import diagnostics


DEVNULL = getattr(subprocess, "DEVNULL", subprocess.PIPE)


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
    output_file.flush()
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


def capture(command, stderr=None, env=None, dry_run=None, echo=True,
            optional=False, allow_non_zero_exit=False):
    """
    Execute the given command and return the standard output.

    This function will raise an exception on any command failure.

    command -- the command to be run.
    stderr -- stderr to be passed to the subprocess.
    env -- custom environment variables of the command.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    optional -- TODO
    allow_non_zero_exit -- TODO
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        echo_command(dry_run, command, env=env)
    if dry_run:
        return

    _env = None

    if env is not None:
        _env = dict(os.environ)
        _env.update(env)
    try:
        out = subprocess.check_output(command, env=_env, stderr=stderr)
        # Coerce to 'str' hack. Not py3 'byte', not py2 'unicode'.
        return str(out.decode())
    except subprocess.CalledProcessError as err:
        if allow_non_zero_exit:
            return err.output
        if optional:
            return None
        diagnostics.fatal(
            "command terminated with a non-zero exit status {}, "
            "aborting".format(str(err.returncode)))
    except OSError as err:
        if optional:
            return None
        diagnostics.fatal(
            "could not execute '{}': {}".format(
                quote_command(command), str(err.strerror)))


@contextmanager
def pushd(path, dry_run=None, echo=True):
    """
    A context manager that allows operating in a different working directory.

    path -- the new working directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    old_dir = os.getcwd()
    if dry_run or echo:
        echo_command(dry_run, ["pushd", path])
    if not dry_run:
        os.chdir(path)
    yield
    if dry_run or echo:
        echo_command(dry_run, ["popd"])
    if not dry_run:
        os.chdir(old_dir)


def makedirs(path, dry_run=None, echo=True):
    """
    Create a directory recursively.

    path -- the directory to create.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        echo_command(dry_run, ['mkdir', '-p', path])
    if dry_run:
        return
    if not os.path.isdir(path):
        os.makedirs(path)


def rmtree(path, dry_run=None, echo=True, ignore_errors=False):
    """
    Remove a directory.

    path -- path to the directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    ignore_errors -- whether or not errors should be ignored.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        echo_command(dry_run, ['rm', '-rf', path])
    if dry_run:
        return
    if os.path.exists(path):
        shutil.rmtree(path, ignore_errors=ignore_errors)


def rm(file, dry_run=None, echo=True):
    """
    Remove a file.

    path -- path to the file.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        echo_command(dry_run, ['rm', file])
    if dry_run:
        return
    if os.path.islink(file):
        os.unlink(file)
    if os.path.exists(file):
        os.remove(file)


def copytree(src, dest, dry_run=None, echo=True):
    """
    Copy a directory recursively.

    src -- path to the directory.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        echo_command(dry_run, ['cp', '-r', src, dest])
    if dry_run:
        return
    if os.path.exists(dest):
        distutils.dir_util.copy_tree(src, dest)
    else:
        shutil.copytree(src, dest)


def copy(src, dest, dry_run=None, echo=True):
    """
    Copy a file.

    path -- path to the file.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        echo_command(dry_run, ['cp', src, dest])
    if dry_run:
        return
    shutil.copy(src, dest)


def unzip(path, dest=None, dry_run=None, echo=True):
    """
    Extract a zip archive.

    path -- path to the archive.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        if dest:
            echo_command(dry_run, ["tar", "-xf", path, "-C", dest])
        else:
            echo_command(dry_run, ["tar", "-xf", path])
    if dry_run:
        return
    with zipfile.ZipFile(path, "r") as archive:
        if dest:
            archive.extractall(dest)
        else:
            archive.extractall()


def tar(path, dest=None, dry_run=None, echo=True):
    """
    Extract an archive.

    path -- path to the archive.
    dest -- the destination directory.
    dry_run -- whether or not to command is only printed.
    echo -- whether or not the command is echoed before the execution.
    """
    dry_run = _coerce_dry_run(dry_run)
    if dry_run or echo:
        if dest:
            echo_command(dry_run, ["tar", "-xf", path, "-C", dest])
        else:
            echo_command(dry_run, ["tar", "-xf", path])
    if dry_run:
        return
    if path.endswith(".zip"):
        with zipfile.ZipFile(path, "r") as archive:
            if dest:
                archive.extractall(dest)
            else:
                archive.extractall()
    else:
        if path.endswith(".tar") or path.endswith(".tar.gz"):
            with tarfile.open(path) as archive:
                if dest:
                    archive.extractall(dest)
                else:
                    archive.extractall()
        else:
            if sys.version_info.major == 2:
                # TODO Use different command for Windows.
                with pushd(os.path.dirname(path)):
                    if dest:
                        call(
                            ["tar", "-xf", os.path.split(path)[1], "-C", dest])
                    else:
                        call(["tar", "-xf", os.path.split(path)[1]])
            else:
                with tarfile.open(path) as archive:
                    if dest:
                        archive.extractall(dest)
                    else:
                        archive.extractall()


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
