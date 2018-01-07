#===-------------------------- checkout.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for LLVM checkout.
"""


import os

from build_utils import shell

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT


def get_dependency():
    """
    Download the LLVM subproducts.
    """
    args = data.build.args
    product = data.build.products.llvm
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))

    llvm_deps = None
    if args.build_libcxx:
        llvm_deps = ["llvm", "libcxx", "libcxxabi"]
    elif args.build_llvm:
        llvm_deps = list(product.subproducts.keys())

    if args.source_llvm or args.build_libcxx:
        for dep in llvm_deps:
            if not skip_download(key=dep):
                single_dependency(key=dep)
    elif args.build_llvm:
        get_llvm_binary()

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))


def inject_version_info(versions):
    """
    Add the LLVM version info to the checkout version info.

    versions -- the version info dictionary of the checkout.
    """
    product = data.build.products.llvm
    args = data.build.args
    version = product.version
    version_info = None
    if args.build_libcxx:
        version_info = {
            "llvm": version,
            "clang": 0,
            "libcxx": version,
            "libcxxabi": version
        }
    elif args.build_llvm:
        version_info = {
            "llvm": version,
            "clang": version,
            "libcxx": version,
            "libcxxabi": version
        }
    versions["llvm"] = version_info
