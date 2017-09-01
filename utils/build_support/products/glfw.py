#===--------------------------- glfw.py -----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the GLFW product helpers.
"""


import os

from .. import shell

from ..variables import ANTHEM_SOURCE_ROOT


def move_checkout_files(build_data):
    """
    """
    product = build_data.products.glfw
    version = product.version

    shell.copytree(
        os.path.join(
            ANTHEM_SOURCE_ROOT, "glfw", version, "glfw-{}".format(version)),
        os.path.join(ANTHEM_SOURCE_ROOT, "glfw", "temp"))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "glfw", version))
    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "glfw", "temp"),
        os.path.join(ANTHEM_SOURCE_ROOT, "glfw", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "glfw", "temp"))
