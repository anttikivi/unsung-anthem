#===--------------------------- llvm.py -----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the LLVM product helpers.
"""


from .. import diagnostics


def checkout_check(build_data, versions):
    """
    """
    diagnostics.note("LLVM checkout is checked when it is downloaded")
    return False
