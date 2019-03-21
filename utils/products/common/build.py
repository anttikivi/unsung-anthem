#===------------------------------- build.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Obliging Ode and Unsung Anthem
builds.
"""


import os
import platform

from build_utils import diagnostics, reflection, shell, which, workspace

from products import common

from script_support import data

from script_support.defaults import COVERAGE_TARGET_MARK

from script_support.variables import ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME


def _config_value(name):
    return reflection.config_value(name)


def do_build(is_ode=False, lib=False, test=False):
    """Build Obliging Ode or Unsung Anthem."""
    args = data.build.args
    toolchain = data.build.toolchain
    ode = data.build.products.ode
    anthem = data.build.products.anthem

    def _copy_scripts():
        if args.enable_gcov and test:
            if is_ode:
                build_dir = reflection.anthem_common_directory_call(
                    "ode_build_dir", lib=lib, test=test)
            else:
                build_dir = reflection.anthem_common_directory_call(
                    "anthem_build_dir", lib=lib, test=test)
            script_dir = os.path.join(
                ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME, "script")
            dest = os.path.join(
                build_dir, _config_value("GCOV_SCRIPT_DIRECTORY_NAME"))
            diagnostics.trace("Copying the scripts from {} to {}".format(
                script_dir, dest))
            shell.copytree(script_dir, dest)

    if lib and test:
        diagnostics.fatal(
            "The CMake script cannot build both 'lib' and 'test' "
            "configurations at the same time")

    if is_ode:
        product = ode
        build_dir = reflection.anthem_common_directory_call(
            "ode_build_dir", lib=lib, test=test)
    else:
        product = anthem
        build_dir = reflection.anthem_common_directory_call(
            "anthem_build_dir", lib=lib, test=test)
    source_dir = os.path.join(ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME)
    if not os.path.exists(source_dir):
        diagnostics.fatal(
            "Cannot find source directory for {} (tried {})".format(
                product.repr, source_dir))

    shell.makedirs(build_dir)

    cmake_env = {"CC": str(toolchain.cc), "CXX": str(toolchain.cxx)}

    cmake_call = reflection.anthem_common_cmake_call(
        "construct_call", is_ode=is_ode, lib=lib, test=test)

    with shell.pushd(build_dir):
        shell.call(cmake_call, env=cmake_env)
        _copy_scripts()
        if args.cmake_generator == "Ninja":
            common.build.ninja()
            common.build.ninja(target="install")
        elif args.cmake_generator == "Unix Makefiles":
            common.build.make()
            common.build.make(target="install")
            if args.enable_gcov and test:
                if is_ode:
                    exe_name = args.ode_name
                else:
                    exe_name = args.anthem_name
                common.build.make(
                    target="{}{}".format(exe_name, COVERAGE_TARGET_MARK),
                    xvfb=True)
                if data.build.ci:
                    shell.call([
                        "coveralls-lcov", "--repo-token",
                        os.environ["ANTHEM_COVERALLS_REPO_TOKEN"],
                        "{}{}.info.cleaned".format(
                            exe_name,
                            COVERAGE_TARGET_MARK)
                    ])

        elif data.build.visual_studio:
            msbuild_args = ["anthem.sln"]
            if args.msbuild_logger is not None:
                msbuild_args += ["/logger:{}".format(args.msbuild_logger)]
            msbuild_args += ["/property:Configuration={}".format(
                args.anthem_build_variant)]
            if platform.system() == "Windows":
                msbuild_args += ["/property:Platform=Win32"]
            common.build.msbuild(args=msbuild_args)
            source_dir = os.path.join(ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME)
            shell.rmtree(os.path.join(build_dir, "script"))
            shell.copytree(os.path.join(source_dir, "script"), os.path.join(
                build_dir, "script"))

    if args.rpath:
        if args.rpath == ".":
            reflection.build_call(
                data.build.products.sdl,
                "copy_dynamic",
                os.path.join(data.build.install_root, "bin"))
            reflection.build_call(
                data.build.products.llvm,
                "copy_dynamic",
                os.path.join(data.build.install_root, "bin"))
        else:
            shell.makedirs(
                os.path.join(data.build.install_root, "bin", args.rpath))
            reflection.build_call(
                data.build.products.sdl,
                "copy_dynamic",
                os.path.join(data.build.install_root, "bin", args.rpath))
            reflection.build_call(
                data.build.products.llvm,
                "copy_dynamic",
                os.path.join(data.build.install_root, "bin", args.rpath))

    if data.build.visual_studio:
        if is_ode:
            variant = args.ode_build_variant
        else:
            variant = args.anthem_build_variant
        reflection.build_call(
            data.build.products.sdl,
            "copy_dynamic",
            os.path.join(build_dir, variant))
