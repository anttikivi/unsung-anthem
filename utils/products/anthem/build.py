#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Unsung Anthem build.
"""


import os
import platform

from build_utils import diagnostics, shell

from products import common, sdl

from script_support import data

from script_support.variables import ANTHEM_REPO_NAME

from . import cmake


def anthem_build_dir(tests=False):
    """
    Create the directory name for the full build subdirectory of Unsung Anthem.

    tests -- whether or not the directory name should be created for the tests
    binaries.
    """
    product = data.build.products.anthem
    if tests:
        return os.path.join(
            data.build.build_root, "{}-{}-{}".format(
                product.identifier, "test", data.build.host_target
            )
        )
    # elif lib:
    #     return os.path.join(
    #         build_data.build_root, "{}-{}-{}".format(
    #             product.identifier, "lib", build_data.host_target
    #         )
    #     )
    return os.path.join(
        data.build.build_root,
        "{}-{}".format(product.identifier, data.build.host_target)
    )


def do_build(tests=False):
    """
    Build Unsung Anthem.

    tests -- whether or not the tests should be built rather than the actual
    executable.
    """
    args = data.build.args
    toolchain = data.build.toolchain
    product = data.build.products.anthem
    build_dir = anthem_build_dir(tests=tests)
    common.build.check_source(key=product.identifier, name=ANTHEM_REPO_NAME)
    shell.makedirs(build_dir)

    cmake_env = {"CC": str(toolchain.cc), "CXX": str(toolchain.cxx)}

    cmake_call = cmake.construct_call(tests=tests)

    with shell.pushd(build_dir):
        shell.call(cmake_call, env=cmake_env, echo=True)
        if args.cmake_generator == "Ninja":
            common.build.ninja()
            common.build.ninja(target="install")
        elif args.cmake_generator == "Unix Makefiles":
            common.build.make()
            if args.enable_gcov and tests:
                common.build.make(
                    target="{}_coverage".format(args.executable_name)
                )
                if data.build.ci:
                    shell.call([
                        "coveralls-lcov", "--repo-token",
                        os.environ["ANTHEM_COVERALLS_REPO_TOKEN"],
                        "{}_coverage.info.cleaned".format(
                            args.executable_name
                        )
                    ])
            common.build.make(target="install")

        elif data.build.visual_studio:
            msbuild_args = ["anthem.sln"]

            if args.msbuild_logger is not None:
                msbuild_args += ["/logger:{}".format(
                    str(args.msbuild_logger)
                )]

            msbuild_args += ["/p:Configuration={}".format(
                args.anthem_build_variant
            )]

            if platform.system() == "Windows":
                msbuild_args += ["/p:Platform=Win32"]

            common.build.msbuild(args=msbuild_args)

    if data.build.visual_studio:
        sdl.build.copy_dynamic(
            os.path.join(build_dir, args.anthem_build_variant)
        )


def should_build():
    """
    Check whether this product should be built.
    """
    return False
