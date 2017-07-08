# anthem_build_support/products/libcxx.py ------------------------*- python -*-
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

from . import product
from .. import (diagnostics, shell)
from ..variables import ANTHEM_SOURCE_ROOT


class Libcxx(product.Product):
    def do_build(self):
        # Delete the libc++ tree from the LLVM tree.
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT,
                                  'llvm',
                                  'projects',
                                  'libcxx'))

        # Copy the libc++ tree to the LLVM tree for the build.
        shell.copytree(self.source_dir,
                       os.path.join(ANTHEM_SOURCE_ROOT,
                                    'llvm',
                                    'projects',
                                    'libcxx'))


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('libc++')):
        diagnostics.fatal('cannot find source directory for libc++ (tried %s)'
                          % (workspace.source_dir('libc++')))

    libcxx_build = Libcxx(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir('libc++'),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'libc++'))

    libcxx_build.do_build()
