#===----------------------------- __init__.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


"""
Wrapper module around the standard argparse that extends the default
functionality with support for multi-destination actions, an expressive DSL for
constructing parsers and more argument types. This module exposes a strict
super-set of the argparse API and is meant to be used as a drop-in replacement.
"""


from argparse import \
    ArgumentDefaultsHelpFormatter, \
    ArgumentError, \
    ArgumentTypeError, \
    FileType, \
    HelpFormatter, \
    Namespace, \
    RawDescriptionHelpFormatter, \
    RawTextHelpFormatter

from argparse import ONE_OR_MORE, OPTIONAL, SUPPRESS, ZERO_OR_MORE

from .actions import Action, Nargs

from .parser import ArgumentParser

from .types import BoolType, PathType, RegexType, ShellSplitType


__all__ = [
    "Action",
    "ArgumentDefaultsHelpFormatter",
    "ArgumentError",
    "ArgumentParser",
    "ArgumentTypeError",
    "HelpFormatter",
    "Namespace",
    "Nargs",
    "RawDescriptionHelpFormatter",
    "RawTextHelpFormatter",

    "BoolType",
    "FileType",
    "PathType",
    "RegexType",
    "ShellSplitType",

    "SUPPRESS",
    "OPTIONAL",
    "ZERO_OR_MORE",
    "ONE_OR_MORE"
]
