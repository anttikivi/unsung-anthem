#===-------------------------- workspace.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the workspace utilities of the build.
"""


import os


def compute_build_subdir(args):
    """
    Create the directory name for the full build subdirectory.

    args -- the command line argument dictionary.
    install -- whether or not the directory should be created for the
    dependency installation.
    """
    version_subdir = args.anthem_version
    cmake_label = args.cmake_generator.replace(" ", "_")
    build_subdir = cmake_label

    # It is not possible to set assertions to SDL at least for now.
    sdl_build_dir_label = args.sdl_build_variant
    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    if args.sdl_build_variant == args.anthem_build_variant:
        build_subdir += anthem_build_dir_label
    else:
        build_subdir += anthem_build_dir_label
        build_subdir += "+sdl-{}".format(sdl_build_dir_label)

    return os.path.join(version_subdir, build_subdir)
