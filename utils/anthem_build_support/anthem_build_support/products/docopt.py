# anthem_build_support/products/docopt.py ------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
docopt build
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


class Docopt(product.Product):
    def do_build(self):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build docopt from.
            call_without_sleeping([self.toolchain.cmake,
                                   self.source_dir,
                                   '-G',
                                   self.args.cmake_generator,
                                   '-DCMAKE_INSTALL_PREFIX='
                                   + self.workspace.install_root])

            # Build the library.
            if self.args.cmake_generator == 'Ninja':
                call_ninja(self.toolchain)
                call_ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                call_make()
                call_make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('docopt')):
        diagnostics.fatal('cannot find source directory for docopt (tried %s)'
                          % (workspace.source_dir('docopt')))

    docopt_build = Docopt(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir('docopt'),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'docopt'))

    docopt_build.do_build()


def bazel(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('docopt')):
        diagnostics.fatal('cannot find source directory for docopt (tried %s)'
                          % (workspace.source_dir('docopt')))

    docopt_build = Docopt(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir('docopt'),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'docopt'))

    docopt_build.bazel()
