#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Ninja build.
"""


import os
import platform
import sys

from build_utils import shell, workspace

from products import common

from script_support import data


def ninja_build_bin_path():
    """
    Create the path for the binary of Ninja in the build directory.
    """
    build_dir = workspace.build_dir(
        product=data.build.products.ninja,
        target="build")
    if platform.system() == "Windows":
        return os.path.join(build_dir, "ninja.exe")
    return os.path.join(build_dir, "ninja")


def ninja_bin_path():
    """
    Create the path for the binary of Ninja.
    """
    if platform.system() == "Windows":
        return os.path.join(data.build.local_root, "bin", "ninja.exe")
    return os.path.join(data.build.local_root, "bin", "ninja")


def _build():
    product = data.build.products.ninja

    build_dir = workspace.build_dir(product=product, target="build")
    source_dir = workspace.source_dir(product=product)

    if common.build.binary_exists(product=product, path=ninja_bin_path()):
        return

    shell.rmtree(build_dir)
    # Ninja can only be built in-tree.
    shell.copytree(source_dir, build_dir)

    if os.path.exists(ninja_build_bin_path()):
        shell.rm(ninja_bin_path())
        if not os.path.isdir(os.path.join(data.build.local_root, "bin")):
            shell.makedirs(os.path.join(data.build.local_root, "bin"))
        shell.copy(ninja_build_bin_path(), ninja_bin_path())
        return

    toolchain = data.build.toolchain

    env = None
    if platform.system() == "Darwin":
        from build_utils import xcrun
        sysroot = xcrun.sdk_path("macosx")
        osx_version_min = data.build.args.darwin_deployment_version
        assert sysroot is not None
        env = {
            "CC": toolchain.cc,
            "CXX": toolchain.cxx,
            "CFLAGS": (
                "-isysroot {sysroot} -mmacosx-version-min={osx_version}"
            ).format(sysroot=sysroot, osx_version=osx_version_min),
            "LDFLAGS": "-mmacosx-version-min={osx_version}".format(
                osx_version=osx_version_min)
        }
    elif toolchain.cxx:
        env = {"CC": toolchain.cc, "CXX": toolchain.cxx}

    with shell.pushd(build_dir):
        shell.call([sys.executable, "configure.py", "--bootstrap"], env=env)

    shell.rm(ninja_bin_path())
    shell.copy(ninja_build_bin_path(), ninja_bin_path())


def do_build():
    """
    Builds Ninja.
    """
    product = data.build.products.ninja
    common.build.check_source(product.identifier)
    _build()
    data.build.toolchain.ninja = ninja_bin_path()
    shell.call(["chmod", "+x", str(ninja_bin_path())])


def should_build():
    """
    Check whether this product should be built.
    """
    args = data.build.args
    toolchain = data.build.toolchain
    cmake_requires_ninja = \
        args.cmake_generator == "Ninja" or args.cmake_generator == "Xcode"
    toolchain_requires = (cmake_requires_ninja and toolchain.ninja is None)
    return args.build_ninja or toolchain_requires
