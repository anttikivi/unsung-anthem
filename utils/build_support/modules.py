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
import sys

from . import diagnostics


def product_call(product, function, *args, **kwargs):
    """
    """
    package = "build_support.products.{}".format(product.identifier)
    diagnostics.trace("Importing package {}".format(package))
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    getattr(product_module, function)(*args, **kwargs)


def product_function_exists(product, function):
    package = "build_support.products.{}".format(product.identifier)
    diagnostics.trace(
        "Importing package {} for checking whether function {} exists".format(
            package, function
        )
    )
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    return hasattr(product_module, function)


def product_exists(product):
    package = "build_support.products.{}".format(product.identifier)
    diagnostics.trace("Looking for package {}".format(package))
    if sys.version_info.major >= 3:
        if sys.version_info.minor >= 4:
            return importlib.util.find_spec(package) is not None
        else:
            return importlib.find_loader(package) is not None
    import imp
    try:
        result = imp.find_module(package)
        return result
    except ImportError:
        return False
