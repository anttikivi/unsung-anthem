# anthem_build_support/diagnostics.py -----------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

from __future__ import print_function

import sys


def note(message):
    """
    note(message)

    Print a diagnostic notification to the standard output.
    """
    print(sys.argv[0] + ": note: " + message)
    sys.stdout.flush()


def fatal(message):
    """
    fatal(message)

    Raise a fatal error.
    """
    raise SystemExit(sys.argv[0] + ": fatal error: " + message)
