# anthem_build_support/products/anthem.py -------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
Unsung Anthem build
"""
# ----------------------------------------------------------------------------

import os
import platform

from . import product
from .. import diagnostics, shell
from ..variables import ANTHEM_REPO_NAME


class Anthem(product.Product):
    def do_build(self, tests=False):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Create CMake call.
        cmake_call = [self.toolchain.cmake,
                      self.source_dir,

                      # Set the CMake generator.
                      '-G', self.args.cmake_generator,

                      '-DCMAKE_BUILD_TYPE='
                      '{}'.format(self.args.anthem_build_variant),

                      # Set the install prefix to the directory in which all of
                      # the dependencies are installed.
                      '-DANTHEM_INSTALL_PREFIX=' + self.workspace.install_root,

                      # Set the C++ standard version as it is required.
                      '-DANTHEM_CXX_VERSION=' + self.args.std,

                      # Set the name of the executable.
                      '-DANTHEM_EXECUTABLE_NAME=' + self.args.executable_name,

                      # Set the name of the executable.
                      '-DANTHEM_TEST_EXECUTABLE_NAME='
                      + self.args.test_executable_name,

                      # Set the main tool for some CMake configurations.
                      '-DANTHEM_MAIN_COMPILER_TOOL='
                      '{}'.format(self.args.main_tool)]

        if self.args.sdl:
            cmake_call += ['-DANTHEM_SDL=ON']
            cmake_call += ['-DANTHEM_GLFW=OFF']
        elif self.args.glfw:
            cmake_call += ['-DANTHEM_SDL=OFF']
            cmake_call += ['-DANTHEM_GLFW=ON']

        if self.args.anthem_assertions:
            cmake_call += ['-DANTHEM_ENABLE_ASSERTIONS=ON']
        else:
            cmake_call += ['-DANTHEM_ENABLE_ASSERTIONS=OFF']

        if not tests:
            cmake_call += ['-DANTHEM_EXECUTABLE_TYPE='
                           + ('clion' if self.args.clion else 'anthem')]
        else:
            cmake_call += ['-DANTHEM_EXECUTABLE_TYPE=test']

        if self.args.cmake_generator == 'Ninja':
            cmake_call += ['-DCMAKE_MAKE_PROGRAM=%s' % self.toolchain.ninja]

        # Set the C++ standard library explicitly.
        if self.args.stdlib_set:
            cmake_call += ['-DANTHEM_STDLIB={}'.format(self.args.stdlib)]

        if self.args.build_llvm or self.args.build_libcxx:
            cmake_call += ['-DANTHEM_CUSTOM_LIBCXX=ON']
        else:
            cmake_call += ['-DANTHEM_CUSTOM_LIBCXX=OFF']

        if self.args.cxx_experimental:
            cmake_call += ['-DANTHEM_USE_EXPERIMENTAL_HEADERS=ON']
        else:
            cmake_call += ['-DANTHEM_USE_EXPERIMENTAL_HEADERS=OFF']

        cmake_call += self.args.extra_cmake_options

        # Create the dictionary of environment variables for the CMake call.
        cmake_env = {'CC': self.toolchain.cc, 'CXX': self.toolchain.cxx}

        if not self.args.clion:
            # Change the working directory to the out-of-tree build directory.
            with shell.pushd(self.build_dir):
                # Generate the files to build Unsung Anthem from.
                shell.call_without_sleeping(cmake_call, env=cmake_env)

                # Build.
                if self.args.cmake_generator == 'Ninja':
                    shell.ninja(self.toolchain)

                elif self.args.cmake_generator == 'Unix Makefiles':
                    shell.make()

                    if self.args.enable_gcov and tests:
                        shell.make(self.args.executable_name + '_coverage')

                elif self.args.visual_studio:
                    msbuild_args = ['anthem.sln']

                    if self.args.msbuild_logger is not None:
                        msbuild_args += ['/logger:'
                                         + str(self.args.msbuild_logger)]

                    msbuild_args +=\
                        ['/p:Configuration='
                         '{}'.format(self.args.anthem_build_variant)]

                    if platform.system() == 'Windows':
                        msbuild_args += ['/p:Platform=Win32']

                    shell.msbuild(self.toolchain, msbuild_args)

                elif self.args.cmake_generator == 'Xcode' \
                        and not self.args.disable_xcodebuild:
                    project_name = 'anthem.xcodeproj'
                    shell.xcodebuild(project_name,
                                     self.toolchain,
                                     self.args.anthem_build_variant)

        elif self.args.clion and not self.args.visual_studio:
            diagnostics.note('CMake would be called with the following '
                             'command and environment variables:')
            shell.print_command(command=cmake_call, env=cmake_env)
            diagnostics.note('You can copy the options and variables into your '
                             'CLion settings')


def build(args, toolchain, workspace, tests=False):
    if not os.path.exists(workspace.anthem_source_dir(ANTHEM_REPO_NAME)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem '
                          '(tried %s)'
                          % (workspace.anthem_source_dir(ANTHEM_REPO_NAME)))

    build_dir = workspace.anthem_build_dir(args.host_target, 'anthem')\
        if not tests \
        else workspace.anthem_build_dir(args.host_target, 'anthem-test')

    anthem_build = Anthem(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=
                          workspace.anthem_source_dir(ANTHEM_REPO_NAME),
                          build_dir=build_dir)

    anthem_build.do_build(tests=tests)
