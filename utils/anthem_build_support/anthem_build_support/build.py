# anthem_build_support/build.py ----------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

from products import glfw


def execute(args, toolchain, workspace_obj):
    """
    Executes the build of Unsung Anthem and its dependencies.
    """

    # Start by building the dependencies of Unsung Anthem.

    # Build GLFW.
    glfw.build(args, toolchain, workspace_obj)
