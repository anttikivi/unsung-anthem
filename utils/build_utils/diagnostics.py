#===---------------------------- diagnostics.py --------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing diagnostic logging functions."""


from __future__ import print_function

import sys


ENDC = "\033[0m"
BOLD = "\033[1m"
UNDERLINE = "\033[4m"

RED = "\033[31m"
GREEN = "\033[32m"
ORANGE = "\033[33m"
BLUE = "\033[34m"
PURPLE = "\033[35m"

FAIL = "\033[91m"
OK_GREEN = "\033[92m"
WARNING = "\033[93m"
OK_BLUE = "\033[94m"
HEADER = "\033[95m"


VERBOSE = False

DEBUG = False


def _coerce_verbosity(verbosity_override=None):
    if verbosity_override is None:
        return VERBOSE
    else:
        return verbosity_override


def _coerce_debug(debug_override=None):
    if debug_override is None:
        return DEBUG
    else:
        return debug_override


def _printer(
        level, colour=None, verbosity_check=lambda: True, print_script=False,
        show_type=False):
    def _printer_decorator(func):
        def _wrapper(message):
            executable = sys.argv[0] + ": " if print_script else ""
            message_type = "{}: ".format(level) if show_type else ""
            if colour is not None:
                full_message = "{}{}{}{}{}".format(
                    executable, colour, message_type, func(message), ENDC)
            else:
                full_message = "{}{}{}".format(
                    executable, message_type, func(message))
            if verbosity_check():
                print(full_message)
            sys.stdout.flush()
            return full_message
        return _wrapper
    return _printer_decorator


@_printer(level="trace", verbosity_check=_coerce_verbosity)
def trace(message):
    """Print a trace diagnostic notification to the standard output."""
    return message


@_printer(level="trace", colour=ORANGE, verbosity_check=_coerce_verbosity)
def trace_head(message):
    """Print a trace diagnostic notification to the standard output."""
    return message


@_printer(level="debug", verbosity_check=_coerce_debug)
def debug(message):
    """Print a debug diagnostic notification to the standard output."""
    return message


@_printer(level="debug", colour=OK_GREEN, verbosity_check=_coerce_debug)
def debug_ok(message):
    """Print a debug diagnostic notification to the standard output."""
    return message


@_printer(level="debug", colour=WARNING, verbosity_check=_coerce_debug)
def debug_note(message):
    """Print a debug diagnostic notification to the standard output."""
    return message


@_printer(level="debug", colour=ORANGE, verbosity_check=_coerce_debug)
def debug_head(message):
    """Print a debug diagnostic notification to the standard output."""
    return message


@_printer(level="note", colour=OK_BLUE)
def fine(message):
    """
    Print a diagnostic notification to the standard output notifying some step
    is complete.
    """
    return message


@_printer(level="note", colour=HEADER + BOLD)
def head(message):
    """Print a header diagnostic notification to the standard output."""
    return message


@_printer(level="note")
def note(message):
    """Print a diagnostic notification to the standard output."""
    return message


@_printer(level="warning", colour=WARNING)
def warn(message):
    """Print a warning notification to the standard output."""
    return message


def warning(message):
    """Print a warning notification to the standard output."""
    warn(message=message)


def fatal(message):
    """Raise a fatal error."""
    @_printer(
        level="fatal error", colour=BOLD + FAIL, verbosity_check=lambda: False)
    def _impl(msg):
        return msg
    raise SystemExit(_impl(message))
