# anthem_build_support/products/glfw.py ---------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
"""
GLFW build
"""
# ----------------------------------------------------------------------------

import os
import platform

from . import product
from .. import diagnostics, shell


class Glfw(product.Product):
    def copy_xcodebuild_files(self):
        # Check if the include directory already exists.
        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'include')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'include'))
        elif os.path.isdir(os.path.join(self.workspace.install_root,
                                        'include',
                                        'GLFW')):
            # Otherwise check if there is a previous installation of GLFW and
            # delete it.
            shell.rmtree(os.path.join(self.workspace.install_root,
                                      'include',
                                      'GLFW'))

        # Copy the GLFW directory to the include folder.
        shell.copytree(os.path.join(self.source_dir, 'include', 'GLFW'),
                       os.path.join(self.workspace.install_root,
                                    'include',
                                    'GLFW'))

        # Check if the library directory already exists.
        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'lib')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'lib'))
        else:
            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'libglfw3.a')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'libglfw3.a'))

        # Copy the library.
        shell.copy(os.path.join(self.build_dir,
                                'src',
                                self.args.glfw_build_variant,
                                'libglfw3.a'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'libglfw3.a'))

    def do_build_windows(self):
        # Check whether the libraries of the current version are already
        # installed.
        if os.path.exists(os.path.join(self.workspace.install_root,
                                       'lib',
                                       'glfw3.lib')) \
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
                                        'GLFW')):
            # Otherwise check if there is a previous installation of GLFW and
            # delete it.
            shell.rmtree(os.path.join(self.workspace.install_root,
                                      'include',
                                      'GLFW'))

        # Copy the GLFW directory to the include folder.
        shell.copytree(os.path.join(self.build_dir, 'include', 'GLFW'),
                       os.path.join(self.workspace.install_root,
                                    'include',
                                    'GLFW'))

        # Check if the library directory already exists.
        if not os.path.isdir(os.path.join(self.workspace.install_root,
                                          'lib')):
            shell.makedirs(os.path.join(self.workspace.install_root,
                                        'lib'))
        else:
            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'glfw3.dll')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'glfw3.dll'))

            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'glfw3.lib')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'glfw3.lib'))

            if os.path.exists(os.path.join(self.workspace.install_root,
                                           'lib',
                                           'glfw3dll.lib')):
                shell.rm(os.path.join(self.workspace.install_root,
                                      'lib',
                                      'glfw3dll.lib'))

        # Copy the libraries directory to the include folder.
        shell.copy(os.path.join(self.build_dir, 'lib-vc2015', 'glfw3.dll'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'glfw3.dll'))
        shell.copy(os.path.join(self.build_dir, 'lib-vc2015', 'glfw3.lib'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'glfw3.lib'))
        shell.copy(os.path.join(self.build_dir, 'lib-vc2015', 'glfw3dll.lib'),
                   os.path.join(self.workspace.install_root,
                                'lib',
                                'glfw3dll.lib'))

    def do_build(self):
        # Check whether the libraries of the current version are already
        # installed.
        if os.path.exists(os.path.join(self.workspace.install_root,
                                       'lib',
                                       'libglfw3.a')) \
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
                      '{}'.format(self.args.glfw_build_variant)]

        if use_ninja:
            cmake_call += [
                '-DCMAKE_MAKE_PROGRAM={}'.format(self.toolchain.ninja)]
            cmake_call += ['-G', 'Ninja']
        else:
            cmake_call += ['-G', self.args.cmake_generator]

        if 'clang' in self.toolchain.cc and self.args.travis:
            cmake_call += ['-DCMAKE_CXX_FLAGS=-stdlib=libc++']

        # Change the working directory to the out-of-tree build directory.
        with shell.pushd(self.build_dir):
            # Generate the files to build GLFW from.
            shell.call_without_sleeping(cmake_call)

            # Build the library.
            # TODO MSBuild
            if use_ninja:
                shell.ninja(self.toolchain)
                shell.ninja_install(self.toolchain)
            elif self.args.cmake_generator == 'Unix Makefiles':
                shell.make()
                shell.make_install()
            elif self.args.cmake_generator == 'Xcode':
                project_name = 'GLFW.xcodeproj'
                shell.xcodebuild(project_name,
                                 self.toolchain,
                                 self.args.glfw_build_variant)

                # Copy the files manually to the installation directory.
                self.copy_xcodebuild_files()

def build(args, toolchain, workspace):
    if not os.path.exists(workspace.source_dir('glfw')):
        diagnostics.fatal(
            'cannot find source directory for GLFW (tried {})'.format(
                workspace.source_dir('glfw')))

    glfw_build = Glfw(args=args,
                      toolchain=toolchain,
                      workspace=workspace,
                      source_dir=workspace.source_dir('glfw'),
                      build_dir=workspace.build_dir(args.host_target, 'glfw'))

    if platform.system() == 'Windows':
        # On Windows, the pre-built binaries are used.
        glfw_build.do_build_windows()
    else:
        glfw_build.do_build()
