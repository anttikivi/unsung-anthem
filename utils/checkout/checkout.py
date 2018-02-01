#===-------------------------- checkout.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for setting up the checkout.
"""


import json
import os

from build_utils import diagnostics, reflection

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT, CHECKOUT_FILE

from . import github


def write_version_file(versions, final_write=False):
    """
    Writes the version information to the versions file.

    versions -- the data for the versions of the projects.
    """
    with open(CHECKOUT_FILE, "w") as outfile:
        json.dump(versions, outfile)

    if final_write:
        log_function = diagnostics.debug_ok
    else:
        log_function = diagnostics.debug
    log_function("Wrote the dependency version information to {}".format(
        CHECKOUT_FILE
    ))


def get_product(key, versions):
    """
    Download a product.

    key -- the name of the product.
    versions -- the checkout version information dictionary.
    """
    product = data.build.products[key]
    if product.github_data:
        diagnostics.debug(
            "{} is a GitHub project and it will be downloaded from "
            "GitHub".format(product.repr)
        )
        github.get_dependency(key)
    else:
        diagnostics.debug(
            "GitHub data is not found from {} and, thus, a custom function "
            "is used to download it".format(product.repr)
        )
        reflection.product_checkout_call(product, "get_dependency")

    if "inject_version_info" in product \
            and product.inject_version_info is not None:
        product.inject_version_info(versions=versions)
    else:
        info = {
            "version": product.version,
            "targets": [data.build.host_target]
        }
        versions[key] = info


def update():
    """
    Update the checkout.
    """
    args = data.build.args

    if os.path.isfile(CHECKOUT_FILE):
        with open(CHECKOUT_FILE) as json_file:
            versions = json.load(json_file)
    else:
        versions = {}

    def _skip_repositories():
        toolchain = data.build.toolchain
        skip_list = []

        if not args.build_llvm:
            if not args.build_libcxx:
                skip_list += ["llvm"]
            else:
                skip_list += ["llvm-llvm"]

        if not args.build_cmake and toolchain.cmake is not None:
            skip_list += ["cmake"]

        if not args.build_ninja and toolchain.ninja is not None:
            skip_list += ["ninja"]

        if not args.build_test:
            skip_list += ["catch"]

        return skip_list

    skip_repository_list = _skip_repositories()

    diagnostics.trace("Using {} protocol to make the HTTP calls".format(
        data.build.connection_protocol.upper()
    ))

    diagnostics.trace("The dependencies to be skipped are {}".format(
        skip_repository_list
    ))

    for key in data.build.products.keys():
        product = data.build.products[key]
        name = product.repr
        if key is "ode" or key is "anthem":
            diagnostics.debug(
                "{} should not be updated via the automated checkout "
                "update".format(name)
            )
            continue
        diagnostics.debug(
            "Beginning to process the checkout update of {}".format(name)
        )
        if key in skip_repository_list:
            diagnostics.note(
                "{} is on the list of repositories to be skipped".format(name)
            )
            continue
        if product.anthem_only and not args.build_anthem:
            diagnostics.note(
                "Unsung Anthem is not built and, thus, {} should not be "
                "downloaded".format(product.repr)
            )
        if not args.clean:
            if "skip_checkout" in product and product.skip_checkout:
                diagnostics.note(
                    "{} checkout check is done in the checkout process".format(
                        product.repr
                    )
                )
            else:
                # TODO Cross-compile targets
                if key in versions \
                        and product.version == versions[key]["version"] \
                        and data.build.host_target in versions[key]["targets"]:
                    diagnostics.note(
                        "{} should not be re-downloaded, skipping".format(
                            name
                        )
                    )
                    continue

        get_product(key=key, versions=versions)

        diagnostics.debug_ok(
            "Updating the checkout of {} is complete".format(name)
        )

        write_version_file(versions)

    write_version_file(versions)
