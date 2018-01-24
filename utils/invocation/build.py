#===--------------------------- build.py ---------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for the build invocation.
"""


from build_utils import diagnostics, reflection

from build_utils.mapping import Mapping

from products import common

from script_support import data


def _build_dependencies():
    """
    Build the dependencies of Unsung Anthem.
    """
    data.build["dependencies"] = Mapping()
    data.build.dependencies["build"] = list()

    for product in data.build.products:
        if not product.check_if_tool() \
                and reflection.get_product_build_call(product, "should_build"):
            diagnostics.trace("Entering the build of {}".format(product.repr))
            if not reflection.product_exists(product) \
                    or not reflection.product_function_exists(
                        product=product,
                        function="do_build"):
                diagnostics.trace(
                    "The product package of {} either doesn't exists or "
                    "doesn't contain function 'build'".format(product.repr)
                )
                diagnostics.trace(
                    "Thus, {} will be built using the default copy "
                    "function".format(product.repr)
                )
                common.build.copy_build(
                    product=product,
                    subdir=product.build_subdir
                )
            else:
                reflection.product_call(product, "do_build")
            diagnostics.debug_ok("{} is now built".format(product.repr))


def invoke():
    """
    Build Unsung Anthem and its dependencies.
    """
