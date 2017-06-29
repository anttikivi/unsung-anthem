# anthem_build_support/products/spdlog.py ------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
spdlog build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (diagnostics, shell)


class Spdlog(product.Product):
    def do_build(self):
        # Copy the files from the source directory to the build directory.
        shell.copytree(self.source_dir, self.build_dir)


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('spdlog')):
        diagnostics.fatal('cannot find source directory for spdlog (tried %s)'
                          % (workspace.source_dir('spdlog')))

    spdlog_build = Spdlog(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir('spdlog'),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'spdlog'))

    spdlog_build.do_build()
