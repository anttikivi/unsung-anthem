# anthem_build_support/products/llvm.py --------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
LLVM build
"""
# ----------------------------------------------------------------------------

import os
import platform

from . import product
from .. import (cache_util, diagnostics, shell)
from ..call import (call_ninja,
                    call_ninja_install,
                    call_make,
                    call_make_install)


class LLVM(product.Product):
    @cache_util.reify
    def clang_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'bin', 'clang')
        else:
            return os.path.join(self.workspace.install_root, 'bin', 'clang')

    @cache_util.reify
    def clang_cpp_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'bin', 'clang++')
        else:
            return os.path.join(self.workspace.install_root, 'bin', 'clang++')

    def do_build(self):
        # Check whether the ninja executable is pre-built and already exists.
        if os.path.exists(self.clang_bin_path):
            return

        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        cmake_call = [self.toolchain.cmake,
                      self.source_dir,
                      '-G', self.args.cmake_generator,
                      '-DCMAKE_INSTALL_PREFIX=%s' % self.workspace.install_root]

        if self.args.cmake_generator == 'Ninja':
            cmake_call += ['-DCMAKE_MAKE_PROGRAM=%s' % self.toolchain.ninja]

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build LLVM from.
            shell.call(cmake_call)

            # Build it.
            if self.args.cmake_generator == 'Ninja':
                call_ninja(self.toolchain)
                call_ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                call_make()
                call_make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('llvm')):
        diagnostics.fatal('cannot find source directory for LLVM (tried %s)'
                          % (workspace.source_dir('llvm')))

    llvm_build = LLVM(args=args,
                      toolchain=toolchain,
                      workspace=workspace,
                      source_dir=workspace.source_dir('llvm'),
                      build_dir=workspace.build_dir(args.host_target, 'llvm'))

    llvm_build.do_build()
    toolchain.cc = llvm_build.clang_bin_path
    toolchain.cxx = llvm_build.clang_cpp_bin_path
