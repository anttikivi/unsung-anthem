# anthem_build_support/products/ninja.py --------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Ninja build
"""
# ----------------------------------------------------------------------------

import os.path
import platform
import sys

from . import product
from .. import cache_util, diagnostics, shell


class Ninja(product.Product):
    @cache_util.reify
    def ninja_build_bin_path(self):
        return os.path.join(self.build_dir, 'ninja.exe') \
            if platform.system() == 'Windows' \
            else os.path.join(self.build_dir, 'ninja')

    @cache_util.reify
    def ninja_bin_path(self):
        return os.path.join(self.workspace.install_root, 'bin', 'ninja.exe') \
            if platform.system() == 'Windows' \
            else os.path.join(self.workspace.install_root, 'bin', 'ninja')

    def do_build(self):
        # Check whether the ninja executable is built and already exists.
        if os.path.exists(self.ninja_bin_path) \
                and os.path.exists(self.build_dir):
            return

        # Ninja can only be built in-tree. Copy the source tree to the build
        # directory.
        shell.rmtree(self.build_dir)
        shell.copytree(self.source_dir, self.build_dir)

        # Check whether the ninja executable is pre-built and already exists.
        if os.path.exists(self.ninja_build_bin_path):
            shell.rm(self.ninja_bin_path)

            # Create the binary installation directory if it does not exist.
            if not os.path.isdir(os.path.join(self.workspace.install_root,
                                              'bin')):
                shell.makedirs(os.path.join(self.workspace.install_root,
                                            'bin'))

            shell.copy(self.ninja_build_bin_path, self.ninja_bin_path)
            return

        env = None
        if platform.system() == 'Darwin':
            from .. import xcrun
            sysroot = xcrun.sdk_path('macosx')
            osx_version_min = self.args.darwin_deployment_version
            assert sysroot is not None
            env = {'CC': self.toolchain.cc,
                   'CXX': self.toolchain.cxx,
                   'CFLAGS': (
                       '-isysroot {sysroot} -mmacosx-version-min={osx_version}'
                   ).format(sysroot=sysroot, osx_version=osx_version_min),
                   'LDFLAGS':
                       '-mmacosx-version-min='
                       '{osx_version}'.format(osx_version=osx_version_min)}
        elif self.toolchain.cxx:
            env = {'CC': self.toolchain.cc,
                   'CXX': self.toolchain.cxx}

        with shell.pushd(self.build_dir):
            shell.call([sys.executable, 'configure.py', '--bootstrap'],
                       env=env)

        shell.rm(self.ninja_bin_path)
        shell.copy(self.ninja_build_bin_path, self.ninja_bin_path)


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('ninja')):
        diagnostics.fatal('cannot find source directory for ninja (tried %s)'
                          % (workspace.source_dir('ninja')))

    ninja_build = Ninja(args=args,
                        toolchain=toolchain,
                        workspace=workspace,
                        source_dir=workspace.source_dir('ninja'),
                        build_dir=workspace.build_dir('build', 'ninja'))
    ninja_build.do_build()
    toolchain.ninja = ninja_build.ninja_bin_path

    # Add the executable permission to the Ninja binary.
    shell.call(['chmod', '+x', str(ninja_build.ninja_bin_path)])
