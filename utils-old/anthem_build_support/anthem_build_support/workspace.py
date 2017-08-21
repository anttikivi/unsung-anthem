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
import platform


class Workspace(object):
    def __init__(self, args, source_root, build_root, tool_build_root,
                 install_root):
        self.args = args
        self.source_root = source_root
        self.build_root = build_root
        self.tool_build_root = tool_build_root
        self.install_root = install_root

    def source_dir(self, path):
        return os.path.join(self.source_root,
                            path,
                            self.args.version_info[path])

    def anthem_source_dir(self, path):
        return os.path.join(self.source_root, path)

    def llvm_source_dir(self, path):
        return os.path.join(self.source_root,
                            'llvm',
                            self.args.llvm_version,
                            path)

    def build_dir(self, deployment_target, product):
        return os.path.join(self.tool_build_root,
                            '%s-%s' % (product, deployment_target),
                            self.args.version_info[product])

    def anthem_build_dir(self, deployment_target, product):
        return os.path.join(self.build_root, '%s-%s' % (product,
                                                        deployment_target))

    def llvm_build_dir(self, deployment_target, product):
        return os.path.join(self.tool_build_root,
                            '%s-%s' % (product, deployment_target),
                            self.args.llvm_version)

    def libcxx_build_dir(self, deployment_target, product):
        return os.path.join(self.tool_build_root,
                            '%s-%s' % (product, deployment_target),
                            self.args.llvm_version)


def compute_subdir(args, shared, install):
    version_subdir = args.anthem_version

    cmake_subdir = args.cmake_generator.replace(" ", "_")

    if args.build_llvm:
        llvm_build_dir_label = args.llvm_build_variant
        if args.llvm_assertions:
            llvm_build_dir_label += "Assert"

        compiler_subdir = "llvm-" \
                          + args.llvm_version + '-' + llvm_build_dir_label

    elif args.build_gcc:
        compiler_subdir = "gcc-" + args.gcc_version
    else:
        if args.main_tool == 'clang' or args.main_tool == 'llvm':
            compiler_subdir = "system-llvm"
        else:
            compiler_subdir = "system-" + args.main_tool

    if args.sdl:
        if platform.system() == "Windows":
            sdl_build_dir_label = "visual-c++"
        else:
            sdl_build_dir_label = args.sdl_build_variant

        framework_subdir = "sdl-" \
                           + args.sdl_version + "-" + sdl_build_dir_label

    else:
        # It is not possible to set assertions to GLFW at least for now.
        glfw_build_dir_label = args.glfw_build_variant

        framework_subdir = "glfw-" \
                           + args.glfw_version + "-" + glfw_build_dir_label

    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    subdir = anthem_build_dir_label

    directory = os.path.join(version_subdir,
                             cmake_subdir,
                             compiler_subdir,
                             framework_subdir,
                             subdir) \
        if not shared else os.path.join('shared', cmake_subdir)

    if install:
        return os.path.join(directory, 'local')
    else:
        return directory


def compute_build_subdir(args):
    return compute_subdir(args, False, False)


def compute_install_prefix(args):
    return compute_subdir(args, False, True)


def compute_shared_build_subdir(args):
    return compute_subdir(args, True, False)


def compute_shared_install_prefix(args):
    return compute_subdir(args, True, True)