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


def source_dir(source_root, path):
    return os.path.join(source_root, path)


def build_dir(build_root, deployment_target, product):
    return os.path.join(build_root, '%s-%s' % (product, deployment_target))


def compute_build_subdir(args):
    # Create a name for the build directory.
    build_subdir = args.cmake_generator.replace(" ", "_")

    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    build_subdir += "+anthem-" + anthem_build_dir_label

    return build_subdir
