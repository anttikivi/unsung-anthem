# anthem_build_support/workspace.py -------------------------------*- python -*-
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
    def __init__(self, args, source_root, build_root, install_root):
        self.args = args
        self.source_root = source_root
        self.build_root = build_root
        self.install_root = install_root

    def source_dir(self, path):
        return os.path.join(self.source_root,
                            path,
                            self.args.version_info[path])

    def build_dir(self, deployment_target, product):
        return os.path.join(self.build_root,
                            '%s-%s' % (product, deployment_target),
                            self.args.version_info[product])


def compute_subdir(args):
    # Create a name for the build directory.
    subdir = args.cmake_generator.replace(" ", "_")

    subdir += '{}'

    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    if args.build_llvm:
        llvm_build_dir_label = args.llvm_build_variant
        if args.llvm_assertions:
            llvm_build_dir_label += "Assert"
    else:
        llvm_build_dir_label = "not-built"

    # It is not possible to set assertions to GLFW at least for now.
    glfw_build_dir_label = args.glfw_build_variant

    if (anthem_build_dir_label == llvm_build_dir_label and
            anthem_build_dir_label == glfw_build_dir_label):
        # Use a simple directory name if all projects use the same build
        # type.
        subdir += "-" + anthem_build_dir_label
    elif (anthem_build_dir_label != llvm_build_dir_label and
            anthem_build_dir_label == glfw_build_dir_label):
        # LLVM build type differs.
        subdir += "-" + anthem_build_dir_label
        subdir += "+llvm-" + anthem_build_dir_label
    elif (anthem_build_dir_label == llvm_build_dir_label and
            anthem_build_dir_label != glfw_build_dir_label):
        # GLFW build type differs.
        subdir += "-" + anthem_build_dir_label
        subdir += "+glfw-" + glfw_build_dir_label
    else:
        # We don't know how to create a short name, so just mangle in all
        # the information.
        subdir += "+anthem-" + anthem_build_dir_label
        subdir += "+llvm-" + llvm_build_dir_label
        subdir += "+glfw-" + glfw_build_dir_label

    return subdir


def compute_build_subdir(args):
    return compute_subdir(args).format('')


def compute_install_prefix(args):
    return os.path.join(compute_build_subdir(args), 'install')
