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


def get_version_directory(args):
    return os.path.join(ANTHEM_SOURCE_ROOT, 'llvm', args.version_info['llvm'])


def get_project_directory(args, project):
    return os.path.join(get_version_directory(args), project)


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
        if not self.args.build_libcxx \
                and os.path.exists(self.clang_bin_path) \
                and os.path.exists(self.build_dir):
            return

        # Copy the libc++ files to the correct directory for the build or build
        # libc++.
        libcxx.build(args=self.args,
                     toolchain=self.toolchain,
                     workspace=self.workspace)

        # If only libc++ is built, return.
        if self.args.build_libcxx and not self.args.build_llvm:
            return

        # Copy the clang files to the correct directory for the build.
        clang.build(args=self.args,
                    toolchain=self.toolchain,
                    workspace=self.workspace)

        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        use_ninja = self.args.cmake_generator == 'Ninja' \
            or self.args.cmake_generator == 'Xcode'

        cmake_call = [self.toolchain.cmake,
                      self.source_dir,
                      '-DCMAKE_INSTALL_PREFIX='
                      '{}'.format(self.workspace.install_root),
                      '-DCMAKE_BUILD_TYPE='
                      '{}'.format(self.args.llvm_build_variant)]

        if self.args.llvm_assertions:
            cmake_call += ['-DLLVM_ENABLE_ASSERTIONS=ON']
        else:
            cmake_call += ['-DLLVM_ENABLE_ASSERTIONS=OFF']

        if self.args.libcxx_assertions:
            cmake_call += ['-DLIBCXX_ENABLE_ASSERTIONS=ON']
        else:
            cmake_call += ['-DLIBCXX_ENABLE_ASSERTIONS=OFF']

        if use_ninja:
            cmake_call += [
                '-DCMAKE_MAKE_PROGRAM={}'.format(self.toolchain.ninja)]
            cmake_call += ['-G', 'Ninja']
        else:
            cmake_call += ['-G', self.args.cmake_generator]

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build LLVM from.
            shell.call(cmake_call)

            # Build it.
            if use_ninja:
                shell.ninja(self.toolchain)
                shell.ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                shell.make()
                shell.make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.llvm_source_dir('llvm')) \
            and args.build_llvm:
        diagnostics.fatal('cannot find source directory for LLVM (tried %s)'
                          % (workspace.llvm_source_dir('llvm')))

    llvm_build = LLVM(args=args,
                      toolchain=toolchain,
                      workspace=workspace,
                      source_dir=workspace.llvm_source_dir('llvm'),
                      build_dir=workspace.llvm_build_dir(args.host_target,
                                                         'llvm'))

    llvm_build.do_build()

    if args.build_llvm:
        toolchain.cc = llvm_build.clang_bin_path
        toolchain.cxx = llvm_build.clang_cxx_bin_path

        args.main_tool = 'clang'
