# anthem_build_support/cmake.py ----------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


def resolve_cmake_generator(raw_opts):
    if raw_opts['--ninja']:
        return 'Ninja'
    elif raw_opts['--make']:
        return 'Unix Makefile'
    elif raw_opts['--xcode']:
        return 'Xcode'
    else:
        return 'Ninja'
