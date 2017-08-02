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


def note(message, print_script=False):
    """
    Print a diagnostic notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    """
    if print_script:
        print(sys.argv[0] + ": note: " + message)
    else:
        print("note: " + message)

    sys.stdout.flush()


def warn(message, print_script=False):
    """
    Print a warning notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    """
    if print_script:
        print(sys.argv[0] + ": " + WARNING + "warning: " + message + ENDC)
    else:
        print(WARNING + "warning: " + message + ENDC)

    sys.stdout.flush()


def warning(message, print_script=False):
    """
    Print a warning notification to the standard output.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    """
    warn(message=message, print_script=print_script)


def fatal(message, print_script=False):
    """
    Raise a fatal error.

    message -- the message to be printed.
    print_script -- whether or not the script file should be printed.
    """
    if print_script:
        raise SystemExit(sys.argv[0]
                         + ": "
                         + FAIL
                         + "fatal error: "
                         + message + ENDC)
    else:
        raise SystemExit(FAIL + "fatal error: " + message + ENDC)
