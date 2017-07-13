# anthem_build_support/products/anthem.py ------------------------*- python -*-
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

import json
import os

from . import product
from .. import (diagnostics, shell)
from ..call import (call_without_sleeping, call_ninja, call_make)
from ..variables import ANTHEM_REPO_NAME


class Anthem(product.Product):
    def do_build(self):
        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        # Create CMake call.
        cmake_call = [self.toolchain.cmake,
                      self.source_dir,

                      # Set the CMake generator.
                      '-G', self.args.cmake_generator,

                      #  Set the executable type to 'anthem' as it will build
                      # the actual executable.
                      '-DANTHEM_EXECUTABLE_TYPE='
                      + ('clion' if self.args.clion else 'anthem'),

                      # Set the install prefix to the directory in which all of
                      # the dependencies are installed.
                      '-DANTHEM_INSTALL_PREFIX=' + self.workspace.install_root,

                      # Set the C++ standard version as it is required.
                      '-DANTHEM_CPP_VERSION=' + self.args.std,

                      # Set the name of the executable.
                      '-DANTHEM_EXECUTABLE_NAME=' + self.args.executable_name]

        if self.args.cmake_generator == 'Ninja':
            cmake_call += ['-DCMAKE_MAKE_PROGRAM=%s' % self.toolchain.ninja]

        # Set the C++ standard library as it is required.
        if self.args.build_llvm:
            cmake_call += ['-DANTHEM_STDLIB=libc++']
            cmake_call += ['-DANTHEM_LLVM=ON']
        else:
            cmake_call += ['-DANTHEM_DEFAULT_COMPILER=ON']
            cmake_call += ['-DANTHEM_LLVM=OFF']

        # if 'clang' in self.toolchain.cc and self.args.travis:
            # cmake_call += ['-DCMAKE_CXX_FLAGS=-stdlib=libc++ -I=']

        # Create the dictionary of environment variables for the CMake call.
        cmake_env = {
            # Set the C compiler.
            'CC': self.toolchain.cc,

            # Set the C++ compiler.
            'CXX': self.toolchain.cxx
        }

        if not self.args.clion:
            # Change the working directory to the out-of-tree build directory.
            with shell.pushd(self.build_dir):
                # Generate the files to build Unsung Anthem from.
                call_without_sleeping(cmake_call, env=cmake_env)

                # Build.
                if self.args.cmake_generator == 'Ninja':
                    call_ninja(self.toolchain)
                elif self.args.cmake_generator == 'Unix Makefiles':
                    call_make()
        else:
            diagnostics.note('CMake would be called with the following '
                             'command and environment variables:')
            shell.print_command(command=cmake_call, env=cmake_env)
            diagnostics.note('You can copy the options and variables into your '
                             'CLion settings')

    def build_value_file(self):
        return os.path.join(self.build_dir, 'bazel_tokens')

    def bazel(self):
        # Read the values of the last build and check whether the build should
        # be clean.
        if os.path.isfile(self.build_value_file()):
            with open(self.build_value_file()) as f:
                build_value_json = json.load(f)
        else:
            build_value_json = {}

        build_values = {'ANTHEM_EXECUTABLE_NAME': self.args.executable_name,
                        'ANTHEM_CPP_VERSION': self.args.std,
                        'ANTHEM_INSTALL_PREFIX': self.workspace.install_root}

        if not (build_values == build_value_json):
            # Start by copying the files to the build directory.
            shell.rmtree(self.build_dir)
            shell.copytree(self.source_dir, self.build_dir)

            # Read the build file and save its contents after replacing the
            # tokens.
            new_lines = []
            with open(os.path.join(self.source_dir, 'BUILD'), 'r') as f:
                for line in f.readlines():
                    new_line = line

                    for token_key in build_values.keys():
                        new_line = new_line.replace(token_key,
                                                    build_values[token_key])

                    new_lines.append(new_line)

            # Delete the old Bazel build script so the new one can be written.
            shell.rm(os.path.join(self.build_dir, 'BUILD'))

            with open(os.path.join(self.build_dir, 'BUILD'), 'w') as f:
                for line in new_lines:
                    f.write(line)

            # Write the tokens to a JSON file so next time the script do not
            # need to re-process the build script.
            with open(self.build_value_file(), 'w') as outfile:
                json.dump(build_values, outfile)
        else:
            diagnostics.note('The Bazel build script do not need to be '
                             'updated')

        # Run the Bazel command.
        with shell.pushd(self.build_dir):
            shell.call([self.toolchain.bazel,
                        'build',
                        ':' + self.args.executable_name])


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir(ANTHEM_REPO_NAME)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem '
                          '(tried %s)'
                          % (workspace.source_dir(ANTHEM_REPO_NAME)))

    anthem_build = Anthem(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir(ANTHEM_REPO_NAME),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'anthem'))

    anthem_build.do_build()


def bazel(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir(ANTHEM_REPO_NAME)):
        diagnostics.fatal('cannot find source directory for Unsung Anthem '
                          '(tried %s)'
                          % (workspace.source_dir(ANTHEM_REPO_NAME)))

    anthem_build = Anthem(args=args,
                          toolchain=toolchain,
                          workspace=workspace,
                          source_dir=workspace.source_dir(ANTHEM_REPO_NAME),
                          build_dir=workspace.build_dir(args.host_target,
                                                        'anthem'))

    anthem_build.bazel()
