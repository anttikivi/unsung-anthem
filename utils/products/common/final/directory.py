#===----------------------------- directory.py ---------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the directories for Obliging Ode and Unsung
Anthem builds.
"""


import os

from script_support import data


def ode_build_dir(lib=False, test=False):
    """
    Create the directory name for the full build subdirectory of Obliging Ode.
    """
    product = data.build.products.ode
    if test:
        return os.path.join(data.build.build_root, "{}-{}-{}".format(
            product.key, "test", data.build.host_target))
    elif lib:
        return os.path.join(data.build.build_root, "{}-{}".format(
            product.key, data.build.host_target))
    return os.path.join(data.build.build_root, "{}-{}".format(
        product.key, data.build.host_target))


def anthem_build_dir(lib=False, test=False):
    """
    Create the directory name for the full build subdirectory of Unsung Anthem.
    """
    product = data.build.products.anthem
    if test:
        return os.path.join(data.build.build_root, "{}-{}-{}".format(
            product.key, "test", data.build.host_target))
    elif lib:
        return os.path.join(data.build.build_root, "{}-{}-{}".format(
            product.key, "lib", data.build.host_target))
    return os.path.join(data.build.build_root, "{}-{}".format(
        product.key, data.build.host_target))
