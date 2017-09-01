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


import os

import requests

from .. import diagnostics, shell

from ..variables import ANTHEM_SOURCE_ROOT


def skip_checkout(build_data, versions):
    """
    """
    args = build_data.args
    product = build_data.products.llvm
    if args.build_libcxx:
        llvm_deps = ["libcxx"]
    elif args.build_llvm:
        llvm_deps = list(product.subproducts.keys())
    llvm_version_node = versions["llvm"]
    for dep in llvm_deps:
        if llvm_version_node[dep] != product.version:
            return False
    return True


def inject_version_info(build_data, versions):
    """
    """
    product = build_data.products.llvm
    args = build_data.args
    version = product.version
    if args.build_libcxx:
        version_info = {"llvm": 0, "clang": 0, "libcxx": version}
    elif args.build_llvm:
        version_info = {"llvm": version, "clang": version, "libcxx": version}
    versions["llvm"] = version_info


def remove_old_checkout(build_data, key):
    """
    """
    product = build_data.products.llvm
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def remove_libcxx_bad_symlink():
    # FIXME: This is bad, this is hardcoded.
    shell.rm(os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", "libcxx", "test", "std",
        "experimental", "filesystem", "Inputs", "static_test_env",
        "bad_symlink"))


def git_dependency(build_data, key):
    """
    """
    product = build_data.products.llvm
    version = product.version
    remove_old_checkout(build_data=build_data, key=key)

    with shell.pushd(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp")):
        shell.call([
            build_data.toolchain.git,
            "clone",
            product.git_format.format(key=key)])

    if version.startswith("5.0"):
        with shell.pushd(
                os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key)):
            shell.call([build_data.toolchain.git, "checkout", "release_50"])

    # FIXME: This is bad, this is hardcoded.
    if key == "libcxx":
        remove_libcxx_bad_symlink()

    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key),
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def release_dependency(build_data, key):
    """
    """
    diagnostics.warn("TODO")
    product = build_data.products.llvm
    version = product.version
    remove_old_checkout(build_data=build_data, key=key)
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))
    # TODO: protocol=build_data.connection_protocol
    url = product.release_format.format(
        protocol="http", version=version,
        key=product.subproducts[key])
    diagnostics.debug("Streaming an asset from {}".format(url))

    responce = requests.get(url=url, stream=True)

    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", key, "{}.tar.xz".format(key))

    with open(destination, "wb") as destination_file:
        for chunk in responce.iter_content(chunk_size=1024):
            if chunk:
                destination_file.write(chunk)

    diagnostics.debug_ok(
        "Finished streaming an asset to {}".format(destination))


def single_dependency(build_data, key):
    """
    """
    diagnostics.debug("Downloading LLVM subproject {}".format(key))
    version = build_data.products.llvm.version
    if version.startswith("6.0") or version.startswith("5.0"):
        git_dependency(build_data=build_data, key=key)
    else:
        release_dependency(build_data=build_data, key=key)


def get_dependency(build_data):
    """
    """
    args = build_data.args
    product = build_data.products.llvm
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))
    if args.build_libcxx:
        llvm_deps = ["libcxx"]
    elif args.build_llvm:
        llvm_deps = list(product.subproducts.keys())

    for dep in llvm_deps:
        single_dependency(build_data=build_data, key=dep)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp"))
