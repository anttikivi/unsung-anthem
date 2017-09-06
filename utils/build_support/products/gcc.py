#===---------------------------- gcc.py -----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the GCC product helpers.
"""


from .. import diagnostics


def get_dependency(build_data):
    """
    """
    diagnostics.fatal("Downloading {} is not currently supported".format(
        build_data.products.gcc.repr))
