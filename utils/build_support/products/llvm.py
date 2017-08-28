#===---------------------------- llvm.py ----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the LLVM data.
"""


from .. import mapping


def llvm_subproducts(*args, **kwargs):
    """
    Create a mapping of the LLVM subproducts.

    args -- the subproducts.
    kwargs -- the subproducts. The key of the argument is the name of the
    subproduct and the value is a string representing an optional identifier
    for the subproduct if the indentifier is different from the name of the
    subproduct. Otherwise, the subproduct must be passed as a bare string or
    the value must be set to 'None'.
    """

    return mapping.Mapping(*args, **kwargs)
