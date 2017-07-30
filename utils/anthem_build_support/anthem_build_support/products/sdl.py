# anthem_build_support/products/sdl.py ----------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
SDL build
"""
# ----------------------------------------------------------------------------

import os
import platform

from . import product
from .. import diagnostics, shell


class SDL(product.Product):
    def do_build_windows(self):
        # Check whether the libraries of the current version are already
        # installed.
        if os.path.exists(os.path.join(self.workspace.install_root,
                                       'lib',
                                       'SDL2.lib')) \
                and os.path.exists(self.build_dir):
            return

        # Delete the old build directory of cat.
        shell.rmtree(self.build_dir)

        # Copy the files from the source directory to the build directory.
        shell.copytree(self.source_dir, self.build_dir)

        # Check if the include directory already exists.
        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'include')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'include'))
        elif os.path.isdir(os.path.join(self.workspace.install_root,
                                        'include',
                                        'SDL')):
            # Otherwise check if there is a previous installation of cat and
            # delete it.
            shell.rmtree(os.path.join(self.workspace.install_root,
                                      'include',
                                      'SDL'))

        # Copy the headers to the include directory.
        shell.copytree(os.path.join(self.build_dir, 'include'),
                       os.path.join(self.workspace.install_root,
                                    'include',
                                    'SDL'))

        # Check if the library directory already exists.
        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'lib')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'lib'))
        else:
            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'SDL2.dll')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'SDL2.dll'))

            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'SDL2.lib')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'SDL2.lib'))

            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'SDL2main.lib')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'SDL2main.lib'))

            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'SDL2test.lib')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'SDL2test.lib'))

        # Copy the libraries directory to the installation directory.
        shell.copy(os.path.join(self.build_dir, 'lib', 'x86', 'SDL2.dll'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'SDL2.dll'))
        shell.copy(os.path.join(self.build_dir, 'lib', 'x86', 'SDL2.lib'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'SDL2.lib'))
        shell.copy(os.path.join(self.build_dir, 'lib', 'x86', 'SDL2main.lib'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'SDL2main.lib'))

        shell.copy(os.path.join(self.build_dir, 'lib', 'x86', 'SDL2test.lib'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'SDL2test.lib'))

    def do_build(self):
        # Check whether the libraries of the current version are already
        # installed.
        if os.path.exists(os.path.join(self.workspace.install_root,
                                       'lib',
                                       'libSDL2.a')) \
                and os.path.exists(self.build_dir):
            return

        # Make the directory for the out-of-tree build.
        shell.makedirs(self.build_dir)

        use_ninja = self.args.cmake_generator == 'Ninja' \
            or self.args.cmake_generator == 'Xcode'

        cmake_call = [self.toolchain.cmake,
                      self.source_dir,
                      "-DCMAKE_INSTALL_PREFIX="
                      "{}".format(self.workspace.install_root),
                      '-DCMAKE_BUILD_TYPE='
                      '{}'.format(self.args.sdl_build_variant)]

        if use_ninja:
            cmake_call += [
                '-DCMAKE_MAKE_PROGRAM={}'.format(self.toolchain.ninja)]
            cmake_call += ['-G', 'Ninja']
        else:
            cmake_call += ['-G', self.args.cmake_generator]

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build SDL from.
            shell.call_without_sleeping(cmake_call)

            # Build the library.
            # TODO MSBuild
            if use_ninja:
                shell.ninja(self.toolchain)
                shell.ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                shell.make()
                shell.make_install()


def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('sdl')):
        diagnostics.fatal('cannot find source directory for SDL'
                          ' (tried {})'.format(workspace.source_dir('sdl')))

    sdl_build = SDL(args=args,
                    toolchain=toolchain,
                    workspace=workspace,
                    source_dir=workspace.source_dir('sdl'),
                    build_dir=workspace.build_dir(args.host_target, 'sdl'))

    if platform.system() == 'Windows':
        # On Windows, the pre-built binaries are used.
        sdl_build.do_build_windows()
    else:
        sdl_build.do_build()
