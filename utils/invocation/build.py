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


import os
import platform

from build_utils import diagnostics, reflection, shell

from build_utils.mapping import Mapping

from products import anthem, common

from script_support import data


def _build_dependencies():
    """
    Build the dependencies of Unsung Anthem.
    """
    data.build["dependencies"] = Mapping()
    data.build.dependencies["build"] = list()

    for key, product in data.build.products.items():
        should_build = reflection.build_call(product, "should_build")
        if not product.check_if_tool() and should_build:
            diagnostics.trace("Entering the build of {}".format(product.repr))
            if not reflection.product_exists(product) \
                    or not reflection.build_function_exists(
                        product=product,
                        function="do_build"
            ):
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
                reflection.build_call(product, "do_build")
            diagnostics.debug_ok("{} is now built".format(product.repr))
        elif not product.check_if_tool() and not should_build:
            diagnostics.trace("{} is not built".format(product.repr))


def invoke():
    """
    Build Unsung Anthem and its dependencies.
    """
    args = data.build.args

    _build_dependencies()

    anthem.build.do_build(tests=False)

    if args.build_test:
        anthem.build.do_build(tests=True)

        if platform.system() == "Windows":
            tests_run_dir = os.path.join(
                anthem.build.anthem_build_dir(tests=True),
                args.anthem_build_variant
            )
        else:
            tests_run_dir = os.path.join(data.build.install_root, "bin")
        with shell.pushd(tests_run_dir):
            if platform.system() == "Windows":
                test_executable = os.path.join(
                    tests_run_dir,
                    args.test_executable_name + ".exe"
                )
            else:
                test_executable = os.path.join(
                    tests_run_dir,
                    args.test_executable_name
                )
            shell.caffeinate([test_executable], echo=True)
