# anthem_build_support/products/cat.py ----------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
cat build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import diagnostics, shell


class Cat(product.Product):
    def do_build(self):
        # Check whether the headers of the current version are already
        # installed.
        if os.path.exists(os.path.join(self.workspace.install_root,
                                       'include',
                                       'cat')) \
                and os.path.exists(self.build_dir):
            return

        # Delete the old build directory of cat.
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
                                        'cat')):
            # Otherwise check if there is a previous installation of cat and
            # delete it.
            shell.rmtree(os.path.join(self.workspace.install_root,
                                      'include',
                                      'cat'))

        # Copy the cat directory to the include folder.
        shell.copytree(os.path.join(self.build_dir, 'cat'),
                       os.path.join(self.workspace.install_root,
                                    'include',
                                    'cat'))


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('cat')):
        diagnostics.fatal('cannot find source directory for cat (tried %s)'
                          % (workspace.source_dir('cat')))

    cat_build = Cat(args=args,
                    toolchain=toolchain,
                    workspace=workspace,
                    source_dir=workspace.source_dir('cat'),
                    build_dir=workspace.build_dir(args.host_target, 'cat'))

    cat_build.do_build()