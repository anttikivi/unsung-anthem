# anthem_build_support/products/anthem.py ------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Unsung Anthem build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (diagnostics, shell)
from ..call import (call_without_sleeping,
                    call_ninja,
                    call_ninja_install,
                    call_make,
                    call_make_install)
from ..variables import (ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME)


class Anthem(product.Product):
    def do_build(self):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Change the working directory to the out-of-tree build directory.
        os.chdir(self.build_dir)

        # Generate the files to build Unsung Anthem from.
        call_without_sleeping([self.toolchain.cmake,
                               self.source_dir,
                               '-G',
                               self.args.cmake_generator,
                               '-DANTHEM_INSTALL_PREFIX='
                               + self.workspace_obj.install_root])

        # Build.
        if self.args.cmake_generator == 'Ninja':
            call_ninja()
            call_ninja_install()
        elif self.args.cmake_generator == 'Unix Makefiles':
            call_make()
            call_make_install()

        # Change the working directory back to the root directory.
        os.chdir(ANTHEM_SOURCE_ROOT)


def build(args, toolchain, workspace_obj):
    if not os.path.exists(workspace_obj.source_dir(ANTHEM_REPO_NAME)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem '
                          '(tried %s)'
                          % (workspace_obj.source_dir(ANTHEM_REPO_NAME)))

    anthem_build = Anthem(args=args,
                          toolchain=toolchain,
                          workspace_obj=workspace_obj,
                          source_dir=workspace_obj.source_dir(ANTHEM_REPO_NAME),
                          build_dir=workspace_obj.build_dir(args.host_target,
                                                            'anthem'))

    anthem_build.do_build()
