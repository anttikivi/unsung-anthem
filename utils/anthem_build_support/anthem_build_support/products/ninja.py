# anthem_build_support/products/ninja.py -------------------------*- python -*-
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
from .. import (cache_util, diagnostics, shell, workspace)


class Ninja(product.Product):
    @cache_util.reify
    def ninja_bin_path(self):
        return os.path.join(self.build_dir, 'ninja')

    def do_build(self):
        if os.path.exists(self.ninja_bin_path):
            return

        env = None
        if platform.system() == 'Darwin':
            from .. import xcrun
            sysroot = xcrun.sdk_path('macosx')
            osx_version_min = self.args.darwin_deployment_version
            assert sysroot is not None
            env = {'CXX': self.toolchain.cxx,
                   'CFLAGS': (
                       '-isysroot {sysroot} -mmacosx-version-min={osx_version}'
                   ).format(sysroot=sysroot, osx_version=osx_version_min),
                   'LDFLAGS':
                       '-mmacosx-version-min='
                       '{osx_version}'.format(osx_version=osx_version_min)}
        elif self.toolchain.cxx:
            env = {'CXX': self.toolchain.cxx}

        # Ninja can only be built in-tree.  Copy the source tree to the build
        # directory.
        shell.rmtree(self.build_dir)
        shell.copytree(self.source_dir, self.build_dir)
        with shell.pushd(self.build_dir):
            shell.call([sys.executable, 'configure.py', '--bootstrap'],
                       env=env)


def build_ninja(args, toolchain, source_root, build_root):
    if not os.path.exists(workspace.source_dir(source_root, 'ninja')):
        diagnostics.fatal("can't find source directory for ninja (tried %s)"
                          % (workspace.source_dir(source_root, 'ninja')))

    ninja_build = Ninja(args=args,
                        toolchain=toolchain,
                        source_dir=workspace.source_dir(source_root, 'ninja'),
                        build_dir=workspace.build_dir(build_root,
                                                      'build',
                                                      'ninja'))
    ninja_build.do_build()
    toolchain.ninja = ninja_build.ninja_bin_path
