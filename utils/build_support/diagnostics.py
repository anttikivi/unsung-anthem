#===------------------------- diagnostics.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing diagnostic logging functions.
"""

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


def debug(message, print_script=False, show_type=False):
    """
    Print a debug diagnostic notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    show_type -- whether or not to print the type of the command before it.
    """
    executable = sys.argv[0] + ": " if print_script else ""
    message_type = "debug: " if show_type else ""

    print("{}{}{}".format(executable, message_type, message))

    sys.stdout.flush()


def note(message, print_script=False, show_type=False):
    """
    Print a diagnostic notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    show_type -- whether or not to print the type of the command before it.
    """
    executable = sys.argv[0] + ": " if print_script else ""
    message_type = "note: " if show_type else ""

    print("{}{}{}".format(executable, message_type, message))

    sys.stdout.flush()


def warn(message, print_script=False, show_type=False):
    """
    Print a warning notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    show_type -- whether or not to print the type of the command before it.
    """

    executable = sys.argv[0] + ": " if print_script else ""
    message_type = "warning: " if show_type else ""

    print("{}{}{}{}{}".format(executable, WARNING, message_type, message,
                              ENDC))

    sys.stdout.flush()


def warning(message, print_script=False, show_type=False):
    """
    Print a warning notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    show_type -- whether or not to print the type of the command before it.
    """
    warn(message=message, print_script=print_script, show_type=show_type)


def fatal(message, print_script=False, show_type=False):
    """
    Raise a fatal error.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    show_type -- whether or not to print the type of the command before it.
    """

    executable = sys.argv[0] + ": " if print_script else ""
    message_type = "fatal error: " if show_type else ""

    raise SystemExit("{}{}{}{}{}".format(executable, FAIL, message_type,
                                         message, ENDC))
