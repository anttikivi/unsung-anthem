#===-------------------------- checkout.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


"""
The support module containing the utilities for checkouts.
"""


import os

from build_utils import shell

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT


def clean_checkout(key):
    """
    Cleans up the old checkout and creates the directories necessary for the
    new one.

    key -- the name of the project.
    """
    product = data.build.products[key]
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
