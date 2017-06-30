# anthem_build_support/products/bazel.py -------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Bazel build
"""
# ----------------------------------------------------------------------------

import json
import os.path
import platform
import sys

from . import product
from .. import (cache_util, diagnostics, shell)

from update_checkout import SCRIPT_DIR


class Bazel(product.Product):
    @cache_util.reify
    def bazel_bin_path(self):
        return os.path.join(self.build_dir, 'ninja.exe') \
            if platform.system() == 'Windows' \
            else os.path.join(self.build_dir, 'ninja')

    def do_build(self):
        # Copy the source tree to the build directory.
        shell.rmtree(self.build_dir)
        shell.copytree(self.source_dir, self.build_dir)

        update_checkout_config = {}

        # TODO The update-checkout config here.
        with open(os.path.join(SCRIPT_DIR, "update-checkout-config.json")) as f:
            update_checkout_config = json.load(f)

        # Check whether the ninja executable is pre-built and already exists.
        if os.path.exists(self.bazel_bin_path):
            return

        install_name = \
            update_checkout_config['dependencies']['bazel']['asset']['id']

        # Set the permission for calling the installation script.
        shell.call(['chmod', '+x', os.path.join(self.build_dir, install_name)])

        shell.call([os.path.join(self.build_dir, install_name),
                    '--prefix=' + self.workspace.install_root])


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('bazel')):
        diagnostics.fatal('cannot find source directory for bazel (tried %s)'
                          % (workspace.source_dir('bazel')))

    bazel_build = Bazel(args=args,
                        toolchain=toolchain,
                        workspace=workspace,
                        source_dir=workspace.source_dir('bazel'),
                        build_dir=workspace.build_dir('build', 'bazel'))
    bazel_build.do_build()
    toolchain.bazel = bazel_build.bazel_bin_path
