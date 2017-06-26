# anthem_build_support/ninja.py ----------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Utilities for building and using Ninja.
"""
# ----------------------------------------------------------------------------

import os
import platform
import sys

from .. import (cache_util, diagnostics, shell, workspace)


@cache_util.reify
def ninja_bin_path(build_dir):
    return os.path.join(build_dir, 'ninja')


def do_build(source_root, build_root):
    source_dir = workspace.source_dir(source_root, 'ninja')
    build_dir = workspace.build_dir(build_root, 'build', 'ninja')

    if os.path.exists(ninja_bin_path(build_dir)):
        return

    env = None

    # TODO Add the environment configuration for Darwin.

    # if platform.system() == "Darwin":
    #     from .. import xcrun
    #     sysroot = xcrun.sdk_path("macosx")
    #     osx_version_min = self.args.darwin_deployment_version_osx
    #     assert sysroot is not None
    #     env = {
    #         "CXX": self.toolchain.cxx,
    #         "CFLAGS": (
    #             "-isysroot {sysroot} -mmacosx-version-min={osx_version}"
    #         ).format(sysroot=sysroot, osx_version=osx_version_min),
    #         "LDFLAGS": (
    #             "-mmacosx-version-min={osx_version}"
    #         ).format(osx_version=osx_version_min),
    #     }
    # elif self.toolchain.cxx:
    #     env = {
    #         "CXX": self.toolchain.cxx,
    #     }

    # Ninja can only be built in-tree. Copy the source tree to the build
    # directory.
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)

    with shell.pushd(build_dir):
        shell.call([sys.executable, 'configure.py', '--bootstrap'], env=env)


def build_ninja(source_root, build_root):
    if not os.path.exists(workspace.source_dir(source_root, "ninja")):
        diagnostics.fatal("can't find source directory for ninja (tried %s)"
                          % (workspace.source_dir(source_root, "ninja")))

    ninja_build = products.Ninja(
        args=self.args,
        toolchain=self.toolchain,
        source_dir=self.workspace.source_dir("ninja"),
        build_dir=self.workspace.build_dir("build", "ninja"))
    ninja_build.do_build(build_root)
    self.toolchain.ninja = ninja_build.ninja_bin_path
