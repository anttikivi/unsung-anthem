# anthem_build_support/products/cmake.py -------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
CMake build
"""
# ----------------------------------------------------------------------------

import json
import os.path
import platform
import sys

from . import product
from .. import (cache_util, diagnostics, shell)

from update_checkout import SCRIPT_DIR


class CMake(product.Product):
    @cache_util.reify
    def cmake_bin_path(self):
        if 'Windows' == platform.system():
            return os.path.join(self.workspace.install_root,
                                'bin',
                                'cmake.exe')
        elif 'Linux' == platform.system():
            return os.path.join(self.workspace.install_root, 'bin', 'cmake')
        elif 'Darwin' == platform.system():
            return os.path.join(self.workspace.install_root,
                                'bin',
                                'CMake.app',
                                'Contents',
                                'bin',
                                'cmake')

    def do_build(self):
        # Copy the source tree to the build directory.
        shell.rmtree(self.build_dir)
        shell.copytree(self.source_dir, self.build_dir)

        # Check whether the ninja executable is pre-built and already exists.
        if os.path.exists(self.cmake_bin_path):
            return

        shell.copytree(self.source_dir,
                       os.path.join(self.workspace.install_root, 'bin'))


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('cmake')):
        diagnostics.fatal('cannot find source directory for CMake (tried %s)'
                          % (workspace.source_dir('cmake')))

    cmake_build = CMake(args=args,
                        toolchain=toolchain,
                        workspace=workspace,
                        source_dir=workspace.source_dir('cmake'),
                        build_dir=workspace.build_dir('build', 'cmake'))
    cmake_build.do_build()
    toolchain.cmake = cmake_build.cmake_bin_path

    with shell.pushd(os.path.join(workspace.install_root, 'bin')):
        shell.call(['ls', '.'])


def resolve_cmake_generator(raw_opts):
    if raw_opts['--ninja']:
        return 'Ninja'
    elif raw_opts['--make']:
        return 'Unix Makefile'
    elif raw_opts['--xcode']:
        return 'Xcode'
    else:
        return 'Ninja'
