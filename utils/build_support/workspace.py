#===-------------------------- workspace.py ------------------*- python -*-===#
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

from . import shell

from .variables import ANTHEM_SOURCE_ROOT


def is_include_dir_made(build_data):
    """
    Check whether the include directory doesn't exist. If it doesn't exist, it
    is created and the function returns True.

    build_data -- the build data.
    """
    if not os.path.isdir(os.path.join(build_data.install_root, "include")):
        shell.makedirs(os.path.join(build_data.install_root, "include"))
        return True
    return False


def include_file(build_data, path):
    """
    Create the absolute path to a file or a directory in the include directory
    of the current build.

    build_data -- the build data.
    path -- relative path to the file or directory.
    """
    return os.path.join(build_data.install_root, "include", path)


def include_file_exists(build_data, path):
    """
    Check a file or a directory exists in the include directory of the current
    build.

    build_data -- the build data.
    path -- relative path to the file or directory.
    """
    return os.path.isdir(include_file(build_data=build_data, path=path))


def include_dir(build_data, product):
    """
    Create the absolute path a directory in the include directory of the
    current build for the given product.

    build_data -- the build data.
    product -- the product.
    """
    return include_file(build_data=build_data, path=product.identifier)


def include_dir_exists(build_data, product):
    """
    Check a file or a directory exists in the include directory of the current
    build for the given product.

    build_data -- the build data.
    product -- the product.
    """
    return os.path.isdir(include_dir(build_data=build_data, product=product))


def is_lib_dir_made(build_data):
    """
    Check whether the library directory doesn't exist. If it doesn't exist, it
    is created and the function returns True.

    build_data -- the build data.
    """
    if not os.path.isdir(os.path.join(build_data.install_root, "lib")):
        shell.makedirs(os.path.join(build_data.install_root, "lib"))
        return True
    return False


def lib_file(build_data, path):
    """
    Create the absolute path to a file or a directory in the library directory
    of the current build.

    build_data -- the build data.
    path -- relative path to the file or directory.
    """
    return os.path.join(build_data.install_root, "lib", path)


def lib_file_exists(build_data, path):
    """
    Check a file or a directory exists in the library directory of the current
    build.

    build_data -- the build data.
    path -- relative path to the file or directory.
    """
    return os.path.isdir(lib_file(build_data=build_data, path=path))


def lib_dir(build_data, product):
    """
    Create the absolute path a directory in the library directory of the
    current build for the given product.

    build_data -- the build data.
    product -- the product.
    """
    return lib_file(build_data=build_data, path=product.identifier)


def lib_dir_exists(build_data, product):
    """
    Check a file or a directory exists in the library directory of the current
    build for the given product.

    build_data -- the build data.
    product -- the product.
    """
    return os.path.isdir(lib_dir(build_data=build_data, product=product))


def source_dir(product, subproduct=None, name=None):
    """
    Create the absolute path to the source directory of the given product.

    product -- the product.
    subproduct -- a possible subproduct of the product for which the path is
    created.
    name -- a custom name of the source directory.
    """
    if subproduct:
        return os.path.join(
            ANTHEM_SOURCE_ROOT, product.identifier, product.version, subproduct
        )
    if name:
        return os.path.join(ANTHEM_SOURCE_ROOT, name)
    return os.path.join(
        ANTHEM_SOURCE_ROOT, product.identifier, product.version
    )


def build_dir(build_data, product, target=None, subproduct=None):
    """
    Create the absolute path to the build directory of the given product.

    build_data -- the build data.
    product -- the product.
    name -- a custom target name.
    subproduct -- a possible subproduct of the product for which the path is
    created.
    """
    if target:
        return os.path.join(
            build_data.shared_build_root,
            "{}-{}".format(product.identifier, target), product.version
        )
    if subproduct:
        return os.path.join(
            build_data.shared_build_root,
            "{}-{}".format(subproduct, build_data.host_target), product.version
        )
    return os.path.join(
        build_data.shared_build_root,
        "{}-{}".format(product.identifier, build_data.host_target),
        product.version
    )


def compute_subdir(args, shared, install):
    """
    Create the directory name for the full build subdirectory.

    args -- the command line argument dictionary.
    shared -- whether or not the directory should be created for the shared
    build.
    install -- whether or not the directory should be created for the
    dependency installation.
    """
    version_subdir = args.anthem_version
    cmake_label = args.cmake_generator.replace(" ", "_")
    build_subdir = cmake_label
    if args.build_llvm:
        llvm_build_dir_label = args.llvm_build_variant
        if args.llvm_assertions:
            llvm_build_dir_label += "Assert"
    elif args.build_libcxx:
        llvm_build_dir_label = args.libcxx_build_variant
        if args.libcxx_assertions:
            llvm_build_dir_label += "Assert"
    else:
        llvm_build_dir_label = None
    # It is not possible to set assertions to GLFW at least for now.
    glfw_build_dir_label = args.glfw_build_variant
    anthem_build_dir_label = args.anthem_build_variant
    if args.anthem_assertions:
        anthem_build_dir_label += "Assert"

    if not llvm_build_dir_label:
        if args.glfw_build_variant == args.anthem_build_variant:
            build_subdir += anthem_build_dir_label
        else:
            build_subdir += anthem_build_dir_label
            build_subdir += "+glfw-{}".format(glfw_build_dir_label)
    else:
        if (args.glfw_build_variant == args.anthem_build_variant
                and llvm_build_dir_label == anthem_build_dir_label):
            build_subdir += anthem_build_dir_label
        elif (args.glfw_build_variant == args.anthem_build_variant
              and llvm_build_dir_label != anthem_build_dir_label):
            build_subdir += anthem_build_dir_label
            if args.build_llvm:
                build_subdir += "+llvm-{}".format(llvm_build_dir_label)
            elif args.build_libcxx:
                build_subdir += "+libc++-{}".format(llvm_build_dir_label)
        elif (args.glfw_build_variant != args.anthem_build_variant
              and llvm_build_dir_label == anthem_build_dir_label):
            build_subdir += anthem_build_dir_label
            build_subdir += "+glfw-{}".format(glfw_build_dir_label)
        else:
            build_subdir += anthem_build_dir_label
            build_subdir += "+glfw-{}".format(glfw_build_dir_label)
            if args.build_llvm:
                build_subdir += "+llvm-{}".format(llvm_build_dir_label)
            elif args.build_libcxx:
                build_subdir += "+libc++-{}".format(llvm_build_dir_label)
    if not shared:
        directory = os.path.join(version_subdir, build_subdir)
    else:
        directory = os.path.join("shared", cmake_label)
    if install:
        return os.path.join(directory, "local")
    return directory


def compute_build_subdir(args):
    """
    Create the directory name for the full build subdirectory.

    args -- the command line argument dictionary.
    """
    return compute_subdir(args=args, shared=False, install=False)


def compute_install_prefix(args):
    """
    Create the directory name for the full installation subdirectory.

    args -- the command line argument dictionary.
    """
    return compute_subdir(args=args, shared=False, install=True)


def compute_shared_build_subdir(args):
    """
    Create the directory name for the full shared build subdirectory.

    args -- the command line argument dictionary.
    """
    return compute_subdir(args=args, shared=True, install=False)


def compute_shared_install_prefix(args):
    """
    Create the directory name for the full shared installation subdirectory.

    args -- the command line argument dictionary.
    """
    return compute_subdir(args=args, shared=True, install=True)
