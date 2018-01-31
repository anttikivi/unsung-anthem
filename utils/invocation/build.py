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

from products import anthem, common, ode

from script_support import data


def _build_dependencies():
    """
    Build the dependencies of Unsung Anthem.
    """
    args = data.build.args
    data.build["dependencies"] = Mapping()
    data.build.dependencies["build"] = list()

    for key, product in data.build.products.items():
        should_build = reflection.build_call(product, "should_build")
        only_anthem = not args.build_anthem and product.anthem_only
        if not product.check_if_tool() and should_build and not only_anthem:
            diagnostics.trace_head(
                "Entering the build of {}".format(product.repr)
            )
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

    ode_p = data.build.products.ode
    anthem_p = data.build.products.anthem

    if args.build_ode:
        diagnostics.debug_head("Entering the build of {}".format(ode_p.repr))
        ode.build.do_build(lib=True, test=False)

    if args.build_anthem:
        diagnostics.debug_head("Entering the build of {}".format(
            anthem_p.repr
        ))
        anthem.build.do_build(lib=False, test=False)

    if args.build_anthem_lib:
        diagnostics.debug_head("Entering the build of {} library".format(
            anthem_p.repr
        ))
        anthem.build.do_build(lib=True, test=False)

    if args.build_test:
        ode_test = args.build_ode and not args.build_anthem
        if ode_test:
            diagnostics.debug_head("Entering the build of {} tests".format(
                ode_p.repr
            ))
            ode.build.do_build(lib=False, test=True)
        else:
            diagnostics.debug_head("Entering the build of {} tests".format(
                anthem_p.repr
            ))
            anthem.build.do_build(lib=False, test=True)

        if platform.system() == "Windows":
            if ode_test:
                test_run_dir = os.path.join(
                    ode.build.ode_build_dir(lib=False, test=True),
                    args.ode_build_variant
                )
            else:
                test_run_dir = os.path.join(
                    anthem.build.anthem_build_dir(lib=False, test=True),
                    args.anthem_build_variant
                )
        else:
            test_run_dir = os.path.join(data.build.install_root, "bin")
        with shell.pushd(test_run_dir):
            if ode_test:
                exe_name = args.ode_test_name
            else:
                exe_name = args.anthem_test_name
            if platform.system() == "Windows":
                test_executable = os.path.join(
                    test_run_dir,
                    "{}.exe".format(exe_name)
                )
            else:
                test_executable = os.path.join(test_run_dir, exe_name)
            shell.caffeinate([test_executable], echo=True)
