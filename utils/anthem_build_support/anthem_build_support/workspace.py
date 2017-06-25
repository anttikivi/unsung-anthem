# anthem_build_support/workspace.py ------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Represent whole source tree and the build directory
"""
# ----------------------------------------------------------------------------

import os.path


class Workspace(object):
    def __init__(self, source_root, build_root):
        self.source_root = source_root
        self.build_root = build_root

    def source_dir(self, path):
        return os.path.join(self.source_root, path)

    def build_dir(self, deployment_target, product):
        return os.path.join(self.build_root,
                            '%s-%s' % (product, deployment_target))


def compute_build_subdir(args):
    # Create a name for the build directory.
    build_subdir = args.cmake_generator.replace(" ", "_")

    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    build_subdir += "+anthem-" + anthem_build_dir_label

    return build_subdir
