#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for glad build.
"""


import os
import sys

from build_utils import shell, workspace

from products import common

from script_support import data


def do_build():
    """
    Build glad.
    """
    product = data.build.products.glad
    common.build.check_source(product)
    bin_path = os.path.join(data.build.local_root, "src", "glad.c")
    if common.build.binary_exists(product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(product)
    source_dir = workspace.source_dir(product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    with shell.pushd(build_dir):
        shell.call([
            sys.executable, "-m", "glad", "--profile=core",
            "--api=gl={}.{}".format(
                data.build.products.anthem.opengl.version.major,
                data.build.products.anthem.opengl.version.minor),
            "--generator=c-debug", "--spec=gl",
            "--out-path={}".format(data.build.local_root)
        ])


def should_build():
    """
    Check whether this product should be built.
    """
    return True
