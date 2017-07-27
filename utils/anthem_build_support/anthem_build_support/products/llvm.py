# anthem_build_support/products/llvm.py ---------------------------*- python -*-
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

from . import clang, libcxx, product
from .. import cache_util, diagnostics, shell

from ..variables import ANTHEM_SOURCE_ROOT


def get_temp_directory(project):
    return os.path.join(ANTHEM_SOURCE_ROOT, 'llvm', 'temp', project)


def get_project_directory(args, project):
    return os.path.join(ANTHEM_SOURCE_ROOT, 'llvm', args.version_info['llvm'], project)


class LLVM(product.Product):
    @cache_util.reify
    def clang_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'bin', 'clang')
        else:
            return os.path.join(self.workspace.install_root, 'bin', 'clang')

    @cache_util.reify
    def clang_cxx_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'bin', 'clang++')
        else:
            return os.path.join(self.workspace.install_root, 'bin', 'clang++')

    def do_build(self):
        # Check whether the clang executable is pre-built and already exists.
        if os.path.exists(self.clang_bin_path) \
                and os.path.exists(self.build_dir):
            return

        # Copy the clang files to the correct directory for the build.
        clang.build(args=self.args,
                    toolchain=self.toolchain,
                    workspace=self.workspace)

        # Copy the libc++ files to the correct directory for the build.
        libcxx.build(args=self.args,
                     toolchain=self.toolchain,
                     workspace=self.workspace)

        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        cmake_call = [self.toolchain.cmake,
                      self.source_dir,
                      '-G', self.args.cmake_generator,
                      '-DCMAKE_INSTALL_PREFIX='
                      '{}'.format(self.workspace.install_root),
                      '-DCMAKE_BUILD_TYPE='
                      '{}'.format(self.args.llvm_build_variant)]

        if self.args.llvm_assertions:
            cmake_call += ['-DLLVM_ENABLE_ASSERTIONS=ON']
        else:
            cmake_call += ['-DLLVM_ENABLE_ASSERTIONS=OFF']

        if self.args.cmake_generator == 'Ninja':
            cmake_call += ['-DCMAKE_MAKE_PROGRAM=%s' % self.toolchain.ninja]

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build LLVM from.
            shell.call(cmake_call)

            # Build it.
            if self.args.cmake_generator == 'Ninja':
                shell.ninja(self.toolchain)
                shell.ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                shell.make()
                shell.make_install()


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
    toolchain.cxx = llvm_build.clang_cxx_bin_path

    args.main_tool = 'clang'
