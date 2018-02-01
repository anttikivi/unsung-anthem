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

from . import shell


def is_include_dir_made():
    """
    Check whether the local include directory doesn't exist. If it doesn't
    exist, it is created and the function returns True.
    """
    if not os.path.isdir(os.path.join(data.build.local_root, "include")):
        shell.makedirs(os.path.join(data.build.local_root, "include"))
        return True
    return False


def include_file(path):
    """
    Create the absolute path to a file or a directory in the include directory
    of the current build.

    path -- relative path to the file or directory.
    """
    return os.path.join(data.build.local_root, "include", path)


def include_file_exists(path):
    """
    Check whether a file or a directory exists in the include directory of the
    current build.

    path -- relative path to the file or directory.
    """
    return os.path.isdir(include_file(path=path))


def include_dir(product):
    """
    Create the absolute path a directory in the include directory of the
    current build for the given product.

    product -- the product.
    """
    return include_file(path=product.identifier)


def include_dir_exists(product):
    """
    Check a file or a directory exists in the include directory of the current
    build for the given product.

    product -- the product.
    """
    return os.path.isdir(include_dir(product=product))


def is_lib_dir_made():
    """
    Check whether the library directory doesn't exist. If it doesn't exist, it
    is created and the function returns True.
    """
    if not os.path.isdir(os.path.join(data.build.local_root, "lib")):
        shell.makedirs(os.path.join(data.build.local_root, "lib"))
        return True
    return False


def lib_file(path):
    """
    Create the absolute path to a file or a directory in the library directory
    of the current build.

    path -- relative path to the file or directory.
    """
    return os.path.join(data.build.local_root, "lib", path)


def lib_file_exists(path):
    """
    Check a file or a directory exists in the library directory of the current
    build.

    path -- relative path to the file or directory.
    """
    return os.path.isdir(lib_file(path=path))


def source_dir(product, subproject=None, name=None):
    """
    Create the absolute path to the source directory of the given product.

    product -- the product.
    subproject -- a possible subproject of the product for which the path is
    created.
    name -- a custom name of the source directory.
    """
    if product.check_if_source():
        target = "src"
    else:
        target = data.build.host_target
    if subproject:
        return os.path.join(
            ANTHEM_SOURCE_ROOT,
            subproject,
            product.version,
            target
        )
    if name:
        return os.path.join(ANTHEM_SOURCE_ROOT, name)
    return os.path.join(
        ANTHEM_SOURCE_ROOT,
        product.identifier,
        product.version,
        target
    )


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
