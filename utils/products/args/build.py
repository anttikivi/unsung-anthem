#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for args build.
"""


import os
import platform

from build_utils import shell, workspace

from products import common

from script_support import data


def args_build_bin_path():
    """
    Create the path for the binary of args in the build directory.
    """
    build_dir = workspace.build_dir(product=data.build.products.args)
    return os.path.join(build_dir, "args.hxx")


def args_bin_path():
    """
    Create the path for the binary of args.
    """
    return os.path.join(data.build.local_root, "include", "args.hxx")


def _do_windows_build():
    """
    Do the Windows build of args.
    """
    product = data.build.products.args
    bin_path = args_bin_path()
    build_bin_path = args_build_bin_path()

    if common.build.binary_exists(product=product, path=bin_path):
        return

    if os.path.exists(build_bin_path):
        shell.rm(bin_path)
        if not os.path.isdir(os.path.join(data.build.local_root, "include")):
            shell.makedirs(os.path.join(data.build.local_root, "include"))
        shell.copy(build_bin_path, bin_path)
        return


def do_build():
    """
    Build args.
    """
    product = data.build.products.args
    common.build.check_source(product.identifier)
    bin_path = os.path.join(data.build.local_root, "include", "args.hxx")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(product)
    source_dir = workspace.source_dir(product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    if platform.system() == "Windows":
        _do_windows_build()
    else:
        with shell.pushd(build_dir):
            common.build.make(
                target="install",
                extra_args="DESTDIR={}".format(data.build.local_root)
            )


def should_build():
    """
    Check whether this product should be built.
    """
    return True
