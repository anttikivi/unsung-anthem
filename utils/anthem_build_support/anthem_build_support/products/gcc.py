# anthem_build_support/products/gcc.py ----------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
GCC build
"""
# ----------------------------------------------------------------------------

import os
import platform

from . import product
from .. import cache_util, diagnostics, shell

from ..variables import ANTHEM_SOURCE_ROOT


def get_temp_directory(project):
    os.path.join(ANTHEM_SOURCE_ROOT, 'llvm', 'temp', project)


def get_project_directory(args, project):
    os.path.join(ANTHEM_SOURCE_ROOT, 'llvm', args.version_info['llvm'], project)


class GCC(product.Product):
    @cache_util.reify
    def gcc_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'bin', 'gcc')
        else:
            return os.path.join(self.workspace.install_root, 'bin', 'gcc')

    @cache_util.reify
    def gxx_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'bin', 'g++')
        else:
            return os.path.join(self.workspace.install_root, 'bin', 'g++')

    def do_build(self):
        # Check whether the ninja executable is pre-built and already exists.
        if os.path.exists(self.gcc_bin_path):
            return

        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Configure the GCC build.
        with shell.pushd(self.build_dir):
            shell.call([os.path.join(self.source_dir, 'configure'),
                        '--prefix={}'.format(self.workspace.install_root)])

        # Build the GCC.
        with shell.pushd(self.build_dir):
            shell.make()

        # Install the GCC.
        with shell.pushd(self.build_dir):
            shell.make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('gcc')):
        diagnostics.fatal('cannot find source directory for GCC (tried %s)'
                          % (workspace.source_dir('gcc')))

    gcc_build = GCC(args=args,
                    toolchain=toolchain,
                    workspace=workspace,
                    source_dir=workspace.source_dir('gcc'),
                    build_dir=workspace.build_dir(args.host_target, 'gcc'))

    gcc_build.do_build()
    toolchain.cc = gcc_build.gcc_bin_path
    toolchain.cxx = gcc_build.gxx_bin_path

    args.main_tool = 'gcc'
