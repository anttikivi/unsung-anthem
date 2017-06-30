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
        # Delete the old build directory of spdlog.
        shell.rmtree(self.build_dir)

        # Copy the files from the source directory to the build directory.
        shell.copytree(self.source_dir, self.build_dir)

        # Check if the include directory already exists.
        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'include')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'include'))
        elif os.path.isdir(os.path.join(self.workspace.install_root,
                                        'include',
                                        'spdlog')):
            # Otherwise check if there is a previous installation of spdlog
            # and delete it.
            shell.rmtree(os.path.join(self.workspace.install_root,
                                      'include',
                                      'spdlog'))

        # Copy the spdlog directory to the include folder.
        shell.copytree(os.path.join(self.build_dir, 'include', 'spdlog'),
                       os.path.join(self.workspace.install_root,
                                    'include',
                                    'spdlog'))


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


def bazel(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('spdlog')):
        diagnostics.fatal('cannot find source directory for spdlog (tried %s)'
                          % (workspace.source_dir('spdlog')))

    spdlog_build = Spdlog(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir('spdlog'),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'spdlog'))

    spdlog_build.bazel()
