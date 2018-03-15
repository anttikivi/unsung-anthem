#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


"""The support module containing the utilities for builds."""


import os
import platform

from build_utils import diagnostics, shell, workspace

from script_support import data

from script_support.variables import ANTHEM_REPO_NAME, ANTHEM_SOURCE_ROOT


def check_source(product):
    """Check if the source directory of the product exists."""
    source_dir = workspace.source_dir(product)
    if not os.path.exists(source_dir):
        diagnostics.fatal(
            "Cannot find source directory for {} (tried {})".format(
                product.repr, source_dir))


def binary_exists(product, path):
    """Check if the binary for the product exists."""
    if os.path.exists(path):
        diagnostics.debug_note(
            "{} is already built and should not be "
            "re-built".format(product.repr))
        return True
    return False


def ninja(target=None, env=None):
    """Call Ninja on the current build directory."""
    if target:
        if isinstance(target, list):
            ninja_call = [data.build.toolchain.ninja]
            ninja_call += target
            ninja_call += ["-j"]
            ninja_call += [str(data.build.args.build_jobs)]
            shell.call(ninja_call, env=env)
        else:
            shell.call([data.build.toolchain.ninja, target, "-j", str(
                data.build.args.build_jobs)], env=env)
    else:
        shell.call([data.build.toolchain.ninja, "-j", str(
            data.build.args.build_jobs)], env=env)


def make(target=None, extra_args=None, env=None):
    """Call Make."""
    call = [data.build.toolchain.make]
    if target:
        if isinstance(target, list):
            call += target
        else:
            call += [target]
    if extra_args:
        if isinstance(extra_args, list):
            call += extra_args
        else:
            call += [extra_args]
    # call += ["-j"]
    # call += [str(data.build.args.build_jobs)]
    shell.call(call, env=env)


def msbuild(args, target=None, env=None, dry_run=None, echo=False):
    """Call MSBuild."""
    call_command = [data.build.toolchain.msbuild]
    call_command += args
    if target:
        call_command += ["/target:{}".format(target)]
    shell.call(call_command, env=env, dry_run=dry_run, echo=echo)


def build_call(
        product, cmake_args=None, build_targets=None, install_targets=None,
        solution_name=None, source_subdir=None):
    """Build the given product by using CMake and the selected program."""
    build_dir = workspace.build_dir(product=product)
    args = data.build.args
    toolchain = data.build.toolchain
    use_ninja = \
        args.cmake_generator == "Ninja" or args.cmake_generator == "Xcode"

    build_type_key = product.key

    if hasattr(args, "{}_build_variant".format(build_type_key)):
        build_type = getattr(args, "{}_build_variant".format(build_type_key))
    else:
        build_type = None

    if source_subdir:
        source_dir = os.path.join(
            workspace.source_dir(product=product), source_subdir)
    else:
        source_dir = workspace.source_dir(product=product)

    cmake_call = [
        toolchain.cmake, source_dir,
        "-DCMAKE_INSTALL_PREFIX={}".format(data.build.local_root)
    ]

    if build_type:
        cmake_call += ["-DCMAKE_BUILD_TYPE={}".format(build_type)]

    if use_ninja:
        cmake_call += ["-DCMAKE_MAKE_PROGRAM={}".format(toolchain.ninja)]
        cmake_call += ["-G", "Ninja"]
    else:
        cmake_call += ["-G", args.cmake_generator]

    if cmake_args:
        if isinstance(cmake_args, dict):
            for k, v in cmake_args.items():
                if isinstance(v, bool):
                    cmake_call += ["-D{}={}".format(k, ("ON" if v else "OFF"))]
                else:
                    cmake_call += ["-D{}={}".format(k, v)]
        else:
            cmake_call += cmake_args

    # cmake_env = {"CC": toolchain.cc, "CXX": toolchain.cxx}
    cmake_env = {}

    with shell.pushd(build_dir):
        shell.call(cmake_call, env=cmake_env)

        # TODO MSBuild
        if use_ninja:
            if build_targets:
                ninja(target=build_targets)
            else:
                ninja()
            if install_targets:
                ninja(target=install_targets)
            else:
                ninja(target="install")
        elif args.cmake_generator == "Unix Makefiles":
            if build_targets:
                make(target=build_targets)
            else:
                make()
            if install_targets:
                make(target=install_targets)
            else:
                make(target="install")
        elif data.build.visual_studio:
            if solution_name is None:
                msbuild_args = ["{}.sln".format(product.key)]
            else:
                msbuild_args = ["{}.sln".format(solution_name)]

            if args.msbuild_logger is not None:
                msbuild_args += ["/logger:{}".format(args.msbuild_logger)]

            msbuild_args += ["/property:Configuration={}".format(
                args.anthem_build_variant if not build_type else build_type)]

            if platform.system() == "Windows":
                msbuild_args += ["/property:Platform=Win32"]

            msbuild(args=msbuild_args)


def copy_build(product, subdir=None):
    """
    Do a simple copying of files to the correct places for the Unsung Anthem
    build.
    """
    check_source(product)
    bin_path = workspace.include_dir(product=product)
    if binary_exists(product=product, path=bin_path):
        return
    source_dir = workspace.source_dir(product)
    if not workspace.is_include_dir_made() and workspace.include_dir_exists(
            product=product):
        shell.rmtree(bin_path)
    if subdir:
        shell.copytree(os.path.join(source_dir, subdir), bin_path)
    else:
        shell.copytree(source_dir, bin_path)
