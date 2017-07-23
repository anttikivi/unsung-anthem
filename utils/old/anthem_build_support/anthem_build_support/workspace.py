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
    def __init__(self, source_root, build_root, install_root):
        self.source_root = source_root
        self.build_root = build_root
        self.install_root = install_root

    def source_dir(self, path):
        return os.path.join(self.source_root, path)

    def build_dir(self, deployment_target, product):
        return os.path.join(self.build_root,
                            '%s-%s' % (product, deployment_target))


def compute_subdir(args):
    subdir = ''

    if 'bazel' == args.build_system:
        # Create a name for the build directory.
        subdir += 'Bazel-'
    elif 'cmake' == args.build_system:
        subdir += 'CMake-'

    # Create a name for the build directory.
    subdir += args.cmake_generator.replace(" ", "_")

    subdir += '{}'

    llvm_build_dir_label = args.llvm_build_variant
    if args.llvm_assertions:
        llvm_build_dir_label += "Assert"

    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    if llvm_build_dir_label == anthem_build_dir_label and args.build_llvm:
        # Use a simple directory name if all projects use the same build type.
        subdir += "-" + llvm_build_dir_label
    else:
        # We do not know how to create a short name, so just mangle in all
        # the information.
        if args.build_llvm:
            subdir += "+llvm-" + llvm_build_dir_label
            subdir += "+anthem-" + anthem_build_dir_label
        else:
            subdir += "-" + anthem_build_dir_label
            subdir += "+no-llvm"

    return subdir


def compute_build_subdir(args):
    return compute_subdir(args).format('')


def compute_install_prefix(args):
    return compute_subdir(args).format('-install')
