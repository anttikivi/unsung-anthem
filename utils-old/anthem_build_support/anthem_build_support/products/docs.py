# anthem_build_support/products/docs.py ---------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Unsung Anthem documentation build
"""
# ----------------------------------------------------------------------------

import os

from . import product
from .. import diagnostics, shell
from ..variables import ANTHEM_REPO_NAME


class Docs(product.Product):
    def do_build(self):
        # Delete the old build directory.
        shell.rmtree(self.build_dir)

        # Copy the files from the source directory to the build directory.
        shell.copytree(self.source_dir, self.build_dir)

        with shell.pushd(self.build_dir):
            shell.call(['latexmk', '-pdf', 'anthem'])


def build(args, toolchain, workspace):
    docs_dir = os.path.join(ANTHEM_REPO_NAME, 'docs', 'sources')

    if not os.path.exists(workspace.anthem_source_dir(docs_dir)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem docs'
                          '(tried %s)'
                          % (workspace.anthem_source_dir(docs_dir)))

    docs_build = Docs(args=args,
                      toolchain=toolchain,
                      workspace=workspace,
                      source_dir=workspace.anthem_source_dir(docs_dir),
                      build_dir=workspace.anthem_build_dir('build',
                                                           'anthem-docs'))

    # docs_build.do_build()
    diagnostics.note('Sorry, but building the documentation does not do '
                     'anything yet')
