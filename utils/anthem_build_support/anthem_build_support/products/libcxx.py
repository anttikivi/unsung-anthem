# anthem_build_support/products/libcxx.py -------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
libc++ build
"""
# ----------------------------------------------------------------------------

import os
import platform

from . import product
from .. import cache_util, diagnostics, shell


class Libcxx(product.Product):
    @cache_util.reify
    def libcxx_bin_path(self):
        if 'Windows' == platform.system():
            # TODO
            return os.path.join(self.workspace.install_root, 'lib', 'libc++.a')
        else:
            return os.path.join(self.workspace.install_root, 'lib', 'libc++.a')

    def copy_files(self):
        # Delete the libc++ tree from the LLVM tree.
        shell.rmtree(os.path.join(self.workspace.llvm_source_dir('llvm'),
                                  'projects',
                                  'libcxx'))

        # Copy the libc++ tree to the LLVM tree for the build.
        shell.copytree(self.source_dir,
                       os.path.join(self.workspace.llvm_source_dir('llvm'),
                                    'projects',
                                    'libcxx'))

    def do_build(self):
        # Check whether the libc++ binary already exists.
        if self.args.build_libcxx and not self.args.build_llvm \
                and os.path.exists(self.libcxx_bin_path) \
                and os.path.exists(self.build_dir):
            return

        # If LLVM is built, copy only the files and exit.
        if self.args.build_llvm and not self.args.build_libcxx:
            self.copy_files()
            return

        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        cmake_call = [self.toolchain.cmake,
                      self.source_dir,
                      '-G', self.args.cmake_generator,
                      '-DCMAKE_INSTALL_PREFIX='
                      '{}'.format(self.workspace.install_root),
                      '-DCMAKE_BUILD_TYPE='
                      '{}'.format(self.args.libcxx_build_variant)]

        if self.args.libcxx_assertions:
            cmake_call += ['-DLIBCXX_ENABLE_ASSERTIONS=ON']
        else:
            cmake_call += ['-DLIBCXX_ENABLE_ASSERTIONS=OFF']

        if self.args.cmake_generator == 'Ninja':
            cmake_call += ['-DCMAKE_MAKE_PROGRAM=%s' % self.toolchain.ninja]

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build libc++ from.
            shell.call(cmake_call)

            # Build it.
            if self.args.cmake_generator == 'Ninja':
                shell.ninja(self.toolchain)
                shell.ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                shell.make()
                shell.make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.llvm_source_dir('libc++')):
        diagnostics.fatal('cannot find source directory for libc++ (tried %s)'
                          % (workspace.llvm_source_dir('libc++')))

    libcxx_build = Libcxx(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.llvm_source_dir('libc++'),
                          build_dir=workspace.llvm_build_dir(args.host_target,
                                                             'libc++'))

    libcxx_build.do_build()
