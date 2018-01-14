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

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT

from . import cache_util


@cache_util.cached
def source_dir(product, subproject=None, name=None):
    """
    Create the absolute path to the source directory of the given product.

    product -- the product.
    subproject -- a possible subproject of the product for which the path is
    created.
    name -- a custom name of the source directory.
    """
    if subproject:
        return os.path.join(
            ANTHEM_SOURCE_ROOT, product.identifier, product.version, subproject
        )
    if name:
        return os.path.join(ANTHEM_SOURCE_ROOT, name)
    return os.path.join(
        ANTHEM_SOURCE_ROOT, product.identifier, product.version
    )


@cache_util.cached
def build_dir(product, target=None, subproject=None):
    """
    Create the absolute path to the build directory of the given product.

    product -- the product.
    name -- a custom target name.
    subproject -- a possible subproduct of the product for which the path is
    created.
    """
    if target:
        return os.path.join(
            data.build.build_root,
            "{}-{}".format(product.identifier, target),
            product.version)
    if subproject:
        return os.path.join(
            data.build.build_root,
            "{}-{}".format(subproject, data.build.host_target),
            product.version)
    return os.path.join(
        data.build.build_root,
        "{}-{}".format(product.identifier, data.build.host_target),
        product.version)


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
