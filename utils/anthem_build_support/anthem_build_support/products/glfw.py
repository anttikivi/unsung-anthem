# anthem_build_support/products/glfw.py --------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
GLFW build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (cache_util, diagnostics, shell, workspace)
from ..call import call_without_sleeping


class Glfw(product.Product):
    @cache_util.reify
    def ninja_bin_path(self):
        return os.path.join(self.build_dir, 'ninja')

    def do_build(self):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Change the working directory to the out-of-tree build directory.
        os.chdir(self.build_dir)

        # Generate the files to build GLFW from.
        call_without_sleeping([self.toolchain.cmake,
                               self.source_dir,
                               '-G',
                               self.args.cmake_generator])


def build(args, toolchain, source_root, build_root):
    if not os.path.exists(workspace.source_dir(source_root, 'glfw')):
        diagnostics.fatal('cannot find source directory for GLFW (tried %s)'
                          % (workspace.source_dir(source_root, 'glfw')))

    glfw_build = Glfw(args=args,
                      toolchain=toolchain,
                      source_dir=workspace.source_dir(source_root, 'glfw'),
                      build_dir=workspace.build_dir(build_root,
                                                    'hello',  # TODO args.host_target,
                                                    'glfw'))

    glfw_build.do_build()
