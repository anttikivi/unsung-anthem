#===---------------------------- glad.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the glad product helpers.
"""


import os
import sys

from .product import binary_exists, check_source

from .. import shell, workspace


def build(build_data):
    """
    Build glad.

    build_data -- the build data.
    """
    product = build_data.products.glad
    check_source(product=product)
    bin_path = os.path.join(build_data.install_root, "src", "glad.c")
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    source_dir = workspace.source_dir(product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    with shell.pushd(build_dir):
        shell.call([
            sys.executable, "-m", "glad", "--profile=core",
            "--api=gl={}.{}".format(
                build_data.anthem.opengl.version.major,
                build_data.anthem.opengl.version.minor),
            "--generator=c-debug", "--spec=gl",
            "--out-path={}".format(build_data.install_root)
        ])
