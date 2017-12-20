#===--------------------------- ninja.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the ninja product helpers.
"""


import os
import platform
import sys

from .product import binary_exists, check_source

from .. import diagnostics, shell, workspace


def ninja_build_bin_path(build_data):
    """
    Create the path for the binary of Ninja in the build directory.

    build_data -- the build data.
    """
    build_dir = workspace.build_dir(
        build_data=build_data, product=build_data.products.ninja,
        target="build"
    )
    if platform.system() == "Windows":
        return os.path.join(build_dir, "ninja.exe")
    return os.path.join(build_dir, "ninja")


def ninja_bin_path(build_data):
    """
    Create the path for the binary of Ninja.

    build_data -- the build data.
    """
    if platform.system() == "Windows":
        return os.path.join(build_data.install_root, "bin", "ninja.exe")
    return os.path.join(build_data.install_root, "bin", "ninja")


def do_build(build_data):
    """
    Do the build of Ninja.

    build_data -- the build data.
    """
    product = build_data.products.ninja
    bin_path = ninja_bin_path(build_data=build_data)
    build_bin_path = ninja_build_bin_path(build_data=build_data)
    build_dir = workspace.build_dir(
        build_data=build_data, product=product, target="build"
    )
    source_dir = workspace.source_dir(product=product)

    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return

    shell.rmtree(build_dir)
    # Ninja can only be built in-tree.
    shell.copytree(source_dir, build_dir)

    if os.path.exists(build_bin_path):
        shell.rm(bin_path)
        if not os.path.isdir(os.path.join(build_data.install_root, "bin")):
            shell.makedirs(os.path.join(build_data.install_root, "bin"))
        shell.copy(build_bin_path, bin_path)
        return

    toolchain = build_data.toolchain

    env = None
    if platform.system() == "Darwin":
        from .. import xcrun
        sysroot = xcrun.sdk_path("macosx")
        osx_version_min = build_data.args.darwin_deployment_version
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

    shell.rm(bin_path)
    shell.copy(build_bin_path, bin_path)


def set_up(build_data):
    """
    Set Ninja up for the build.

    build_data -- the build data.
    """
    product = build_data.products.ninja
    check_source(product=product)
    do_build(build_data=build_data)
    build_data.toolchain.ninja = ninja_bin_path(build_data=build_data)
    shell.call(["chmod", "+x", str(ninja_bin_path(build_data=build_data))])


def set_toolchain(build_data):
    """
    Set Ninja to the toolchain.

    build_data -- the build data.
    """
    build_data.toolchain.ninja = ninja_bin_path(build_data=build_data)
    diagnostics.debug(
        "Set {} to the toolchain from a custom location: {}".format(
            build_data.products.ninja.repr, build_data.toolchain.ninja))
