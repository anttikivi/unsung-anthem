#===--------------------------- modules.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Python modules.
"""


import importlib

from . import diagnostics


def product_call(product, function, *args, **kwargs):
    """
    """
    package = "build_support.products.{}".format(product.identifier)
    diagnostics.trace("Importing package {}".format(package))
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    getattr(product_module, function)(*args, **kwargs)
