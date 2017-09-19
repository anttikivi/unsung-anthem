#===---------------------------- args.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the args product helpers.
"""


import os
import platform

from .product import binary_exists, check_source

from .. import shell, workspace


def args_build_bin_path(build_data):
    """
    Create the path for the binary of args in the build directory.

    build_data -- the build data.
    """
    build_dir = workspace.build_dir(
        build_data=build_data, product=build_data.products.args
    )
    return os.path.join(build_dir, "args.hxx")


def args_bin_path(build_data):
    """
    Create the path for the binary of args.

    build_data -- the build data.
    """
    return os.path.join(build_data.install_root, "include", "args.hxx")


def do_windows_build(build_data):
    """
    Do the Windows build of args.

    build_data -- the build data.
    """
    product = build_data.products.args
    bin_path = args_bin_path(build_data=build_data)
    build_bin_path = args_build_bin_path(build_data=build_data)

    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return

    if os.path.exists(build_bin_path):
        shell.rm(bin_path)
        if not os.path.isdir(os.path.join(build_data.install_root, "include")):
            shell.makedirs(os.path.join(build_data.install_root, "include"))
        shell.copy(build_bin_path, bin_path)
        return


def build(build_data):
    """
    Build args.

    build_data -- the build data.
    """
    product = build_data.products.args
    check_source(product=product)
    bin_path = os.path.join(build_data.install_root, "include", "args.hxx")
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    source_dir = workspace.source_dir(product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    if platform.system() == "Windows":
        do_windows_build(build_data=build_data)
    else:
        with shell.pushd(build_dir):
            shell.make(
                build_data=build_data, target="install",
                extra_args="DESTDIR={}".format(build_data.install_root))
