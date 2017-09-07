#===-------------------------- workspace.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the workspace utilities of the build.
"""


import os
import platform


def compute_subdir(args, shared, install):
    version_subdir = args.anthem_version

    cmake_subdir = args.cmake_generator.replace(" ", "_")

    if args.build_llvm:
        llvm_build_dir_label = args.llvm_build_variant
        if args.llvm_assertions:
            llvm_build_dir_label += "Assert"

        compiler_subdir = \
            "llvm-" + args.llvm_version + "-" + llvm_build_dir_label
    else:
        if args.main_tool == "clang" or args.main_tool == "llvm":
            compiler_subdir = "system-llvm"
        else:
            compiler_subdir = "system-" + args.main_tool

    if args.sdl:
        if platform.system() == "Windows":
            sdl_build_dir_label = "visual-c++"
        else:
            sdl_build_dir_label = args.sdl_build_variant

        framework_subdir = \
            "sdl-" + args.sdl_version + "-" + sdl_build_dir_label
    else:
        # It is not possible to set assertions to GLFW at least for now.
        glfw_build_dir_label = args.glfw_build_variant

        framework_subdir = \
            "glfw-" + args.glfw_version + "-" + glfw_build_dir_label

    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    subdir = anthem_build_dir_label

    if not shared:
        directory = os.path.join(
            version_subdir, cmake_subdir, compiler_subdir, framework_subdir,
            subdir)
    else:
        directory = os.path.join("shared", cmake_subdir)

    if install:
        return os.path.join(directory, "local")

    return directory


def compute_build_subdir(args):
    return compute_subdir(args=args, shared=False, install=False)


def compute_install_prefix(args):
    return compute_subdir(args=args, shared=False, install=True)


def compute_shared_build_subdir(args):
    return compute_subdir(args=args, shared=True, install=False)


def compute_shared_install_prefix(args):
    return compute_subdir(args=args, shared=True, install=True)
