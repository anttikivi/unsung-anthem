# anthem_build_support/products/clang.py -------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Clang build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (diagnostics, shell)
from ..variables import ANTHEM_SOURCE_ROOT


class Clang(product.Product):
    def do_build(self):
        # Delete the Clang tree from the LLVM tree.
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT,
                                  'llvm',
                                  'tools',
                                  'clang'))

        # Copy the Clang tree to the LLVM tree for the build.
        shell.copytree(self.source_dir,
                       os.path.join(ANTHEM_SOURCE_ROOT,
                                    'llvm',
                                    'tools',
                                    'clang'))


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('clang')):
        diagnostics.fatal('cannot find source directory for Clang (tried %s)'
                          % (workspace.source_dir('clang')))

    clang_build = Clang(args=args,
                        toolchain=toolchain,
                        workspace=workspace,
                        source_dir=workspace.source_dir('clang'),
                        build_dir=workspace.build_dir(args.host_target,
                                                      'clang'))

    clang_build.do_build()
