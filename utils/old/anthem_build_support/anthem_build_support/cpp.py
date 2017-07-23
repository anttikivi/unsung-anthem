# anthem_build_support/cpp.py ------------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


def resolve_standard_version(raw_opts):
    if raw_opts['--std'] is not None:
        return raw_opts['--std']
    elif raw_opts['--c++17']:
        return 'c++17'
    elif raw_opts['--c++14']:
        return 'c++14'
    elif raw_opts['--c++11']:
        return 'c++11'
    else:
        return 'c++14'
