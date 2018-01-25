#===------------------------- reflection.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for Python modules.
"""


import importlib
import sys

from . import diagnostics


PRODUCT_PACKAGE = "products"
CHECKOUT_MODULE = "checkout"
BUILD_MODULE = "build"


def product_call(product, function, *args, **kwargs):
    """
    Call a function in a product module.

    product -- the name of the product.
    function -- the name of the function.
    args -- the positional arguments to be passed into the function.
    kwargs -- the key-value arguments to be passed into the function.
    """
    package = "{}.{}".format(PRODUCT_PACKAGE, product.identifier)
    diagnostics.trace("Importing package {}".format(package))
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    getattr(product_module, function)(*args, **kwargs)


def product_checkout_call(product, function, *args, **kwargs):
    """
    Call a function in a product module.

    product -- the name of the product.
    function -- the name of the function.
    args -- the positional arguments to be passed into the function.
    kwargs -- the key-value arguments to be passed into the function.
    """
    package = "{}.{}.{}".format(
        PRODUCT_PACKAGE,
        product.identifier,
        CHECKOUT_MODULE
    )
    diagnostics.trace("Importing package {}".format(package))
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    getattr(product_module, function)(*args, **kwargs)


def get_build_call(product, function):
    """
    Get a function in a product module.

    product -- the name of the product.
    function -- the name of the function.
    """
    package = "{}.{}.{}".format(
        PRODUCT_PACKAGE,
        product.identifier,
        BUILD_MODULE
    )
    diagnostics.trace("Importing package {}".format(package))
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    return getattr(product_module, function)


def build_call(product, function, *args, **kwargs):
    """
    Call a function in a product module.

    product -- the name of the product.
    function -- the name of the function.
    args -- the positional arguments to be passed into the function.
    kwargs -- the key-value arguments to be passed into the function.
    """
    return get_build_call(product, function)(*args, **kwargs)


def build_function_exists(product, function):
    """
    Check whether a function exists in a product module.

    product -- the name of the product.
    function -- the name of the function.
    """
    package = "{}.{}.{}".format(
        PRODUCT_PACKAGE,
        product.identifier,
        BUILD_MODULE
    )
    diagnostics.trace(
        "Importing package {} for checking whether function {} exists".format(
            package, function
        )
    )
    product_module = importlib.import_module(package)
    diagnostics.trace("Imported package {}".format(package))
    if hasattr(product_module, function):
        diagnostics.trace(
            "Package {} has function '{}'".format(package, function)
        )
    else:
        diagnostics.trace(
            "Package {} doesn't have function '{}'".format(package, function)
        )
    return hasattr(product_module, function)


def product_exists(product):
    """
    Check whether a product module exists.

    product -- the name of the product.
    """
    package = "{}.{}".format(PRODUCT_PACKAGE, product.identifier)
    diagnostics.trace("Looking for package {}".format(package))
    if sys.version_info.major >= 3:
        if sys.version_info.minor >= 4:
            return importlib.util.find_spec(package) is not None
        else:
            return importlib.find_loader(package) is not None
    import imp
    try:
        products_info = imp.find_module(PRODUCT_PACKAGE)
        products = imp.load_module(PRODUCT_PACKAGE, *products_info)
        diagnostics.trace("Found package {}".format(PRODUCT_PACKAGE))

        imp.find_module(product.identifier, products.__path__)
        diagnostics.trace("Found package {}".format(product.identifier))
        return True
    except ImportError:
        return False
