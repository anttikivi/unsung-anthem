#===-------------------------- arguments.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the command line argument helpers.
"""


import argparse
import os
import shlex


__all__ = ["ACTION", "TYPE"]


class _Registry(object):
    pass


def _register(registry, name, value):
    setattr(registry, name, value)


# Types ----------------------------------------------------------------------
TYPE = _Registry()


def type_bool(string):
    """
    Parse a boolean strictly.

    Unlike Python's 'bool()', where 'bool("False")' is 'True', this function
    can be passed as 'type=' argument to argparse to parse values passed to
    command line arguments.

    string -- the string to be parsed.
    """

    if string in ["0", "false", "False"]:
        return False

    if string in ["1", "true", "True"]:
        return True

    raise argparse.ArgumentTypeError("{!r} is not a boolean "
                                     "value".format(string))


_register(TYPE, "bool", type_bool)


def type_shell_split(string):
    """
    Parse and split shell arguments string into a list of shell arguments.

    Recognize ',' as a separator as well as white spaces. For example, string
    '-BAR="foo bar" -BAZ='foo,bar',-QUX 42' is parsed into
    ["-BAR=foo bar", "-BAZ=foo,bar", "-QUX", "42"]

    string -- the string to be parsed.
    """
    lex = shlex.shlex(string, posix=True)
    lex.whitespace_split = True
    lex.whitespace += ","
    return list(lex)


_register(TYPE, "shell_split", type_shell_split)


def type_executable(string):
    """
    Check the string is executable path string.

    Convert it to absolute path.

    string -- the string to be parsed.
    """
    if os.path.isfile(string) and os.access(string, os.X_OK):
        return os.path.abspath(string)

    raise argparse.ArgumentTypeError("{!r} is not executable".format(string))


_register(TYPE, "executable", type_executable)


# Actions --------------------------------------------------------------------
ACTION = _Registry()


class _UnavailableAction(argparse.Action):
    def __init__(self,
                 option_strings,
                 dest=argparse.SUPPRESS,
                 default=argparse.SUPPRESS,
                 nargs="?",
                 help=None):
        super(_UnavailableAction, self).__init__(
            option_strings=option_strings,
            dest=dest,
            default=default,
            nargs=nargs,
            help=help)

    def __call__(self, parser, namespace, values, option_string=None):
        if option_string is not None:
            arg = option_string
        else:
            arg = str(values)
        parser.error("unknown argument: {}".format(arg))


_register(ACTION, "unavailable", _UnavailableAction)


class _ConcatAction(argparse.Action):
    def __call__(self, parser, namespace, values, option_string=None):
        old_val = getattr(namespace, self.dest)
        if old_val is None:
            val = values
        else:
            val = old_val + values
        setattr(namespace, self.dest, val)


_register(ACTION, "concat", _ConcatAction)


class _OptionalBoolAction(argparse.Action):
    def __init__(self,
                 option_strings,
                 dest,
                 default=False,
                 metavar="BOOL",
                 help=None):
        super(_OptionalBoolAction, self).__init__(
            option_strings=option_strings,
            dest=dest,
            default=default,
            metavar=metavar,
            nargs="?",
            type=TYPE.bool,
            help=help,
            const=True)

    def __call__(self, parser, namespace, values, option_string=None):
        setattr(namespace, self.dest, values)


_register(ACTION, "optional_bool", _OptionalBoolAction)
