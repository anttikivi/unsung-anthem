# anthem_build_support/products/test.py --------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Unsung Anthem tests build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (diagnostics, shell)
from ..call import (call_without_sleeping, call_ninja, call_make)
from ..variables import ANTHEM_REPO_NAME


class Test(product.Product):
    def do_build(self):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Create CMake call.
        cmake_call = [self.toolchain.cmake,
                      self.source_dir,

                      # Set the CMake generator.
                      '-G', self.args.cmake_generator,

                      #  Set the executable type to 'anthem' as it will build
                      # the actual executable.
                      '-DANTHEM_EXECUTABLE_TYPE=test',

                      # Set the install prefix to the directory in which all of
                      # the dependencies are installed.
                      '-DANTHEM_INSTALL_PREFIX=' + self.workspace.install_root,

                      # Set the C++ Standard version as it is required.
                      '-DANTHEM_CPP_VERSION=' + self.args.std,

                      # Set the name of the executable.
                      '-DANTHEM_TEST_EXECUTABLE_NAME='
                      + self.args.test_executable_name]

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build Unsung Anthem from.
            call_without_sleeping(cmake_call)

            # Build.
            if self.args.cmake_generator == 'Ninja':
                call_ninja()
            elif self.args.cmake_generator == 'Unix Makefiles':
                call_make()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir(ANTHEM_REPO_NAME)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem '
                          '(tried %s)'
                          % (workspace.source_dir(ANTHEM_REPO_NAME)))

    anthem_build = Test(args=args,
                        toolchain=toolchain,
                        workspace=workspace,
                        source_dir=workspace.source_dir(ANTHEM_REPO_NAME),
                        build_dir=workspace.build_dir(args.host_target,
                                                      'anthem-test'))

    anthem_build.do_build()
