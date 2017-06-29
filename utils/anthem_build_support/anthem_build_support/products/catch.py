# anthem_build_support/products/catch.py -------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Catch build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import (diagnostics, shell)


class Catch(product.Product):
    def do_build(self):
        # Copy the files from the source directory to the build directory.
        shell.copytree(self.source_dir, self.build_dir)

        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'include')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'include'))

        # Copy the header to the include folder.
        shell.copy(os.path.join(self.source_dir, 'catch.hpp'),
                   os.path.join(self.workspace.install_root,
                                'include',
                                'catch.hpp'))


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('catch')):
        diagnostics.fatal('cannot find source directory for Catch (tried %s)'
                          % (workspace.source_dir('catch')))

    catch_build = Catch(args=args,
                        toolchain=toolchain,
                        workspace=workspace,
                        source_dir=workspace.source_dir('catch'),
                        build_dir=workspace.build_dir(args.host_target,
                                                      'catch'))

    catch_build.do_build()
