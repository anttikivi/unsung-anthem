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


import json
import os
import platform

from build_utils import diagnostics, http_stream, shell

from products import libcxx

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT, VERSIONS_FILE


def should_skip_download(key):
    """
    Check whether or not the LLVM download should be skipped.

    key -- the name of the subproject.
    """
    if os.path.isfile(VERSIONS_FILE):
        with open(VERSIONS_FILE) as json_file:
            versions = json.load(json_file)
    else:
        versions = {}

    if "llvm" in versions:
        version_node = versions["llvm"]
        if key in version_node:
            if version_node[key] == data.build.products.llvm.version:
                diagnostics.debug(
                    "{} should not be re-downloaded, skipping".format(key))
                return True
    return False


def remove_old_checkout(key):
    """
    Remove the old checkout of the given LLVM subproject.

    key -- the name of the subproject.
    """
    product = data.build.products.llvm
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def move_project_files(key, subdir):
    """
    Move the LLVM subproduct files to the correct location after the download.

    key -- the name of the subproduct.
    """
    product = data.build.products.llvm
    version = product.version
    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key, subdir),
        os.path.join(ANTHEM_SOURCE_ROOT, "llvm", version, key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))


def get_project_source(key):
    """
    Download the given LLVM subproject.

    key -- the name of the subproject.
    """
    diagnostics.debug("Downloading LLVM subproject {}".format(key))

    product = data.build.products.llvm
    version = product.version
    remove_old_checkout(key)
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))
    url = product.source_format.format(
        protocol=data.build.connection_protocol,
        version=version,
        key=product.subproducts[key])
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", key, "{}.tar.xz".format(key))
    http_stream.stream(url=url, destination=destination)
    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))
    subdir = "{}-{}.src".format(key, version)
    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))
    # FIXME: This is bad, this is hardcoded.
    if key == "libcxx":
        libcxx.remove_bad_symlink(subdir)
    shell.rm(destination)
    move_project_files(key=key, subdir=subdir)


def download_binary():
    """
    Download the pre-built LLVM binary.
    """
    product = data.build.products.llvm
    version = product.version
    key = "llvm"
    remove_old_checkout(key)
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", "llvm"))

    # TODO
    sys = platform.system()
    if sys == "Linux":
        machine = "{}-{}".format("x86_64", product.binary_platforms.ubuntu)
    else:
        machine = "{}-{}".format("x86_64", product.binary_platforms.darwin)
    url = product.binary_format.format(
        protocol=data.build.connection_protocol,
        version=version,
        platform=machine)
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "llvm", "temp", key, "{}.tar.xz".format(key)
    )

    http_stream.stream(url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "llvm", "temp", key))

    subdir_format = "clang+llvm-{version}-{platform}"
    # TODO
    if sys == "Darwin":
        subdir_format = "clang+llvm-{version}-final-{platform}"

    subdir = subdir_format.format(version=version, platform=machine)
    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))
    shell.rm(destination)
    move_project_files(key=key, subdir=subdir)


def get_dependency():
    """
    Download the LLVM subproducts.
    """
    # TODO: If for some reason LLVM is downloaded on Windows, stop it as LLVM
    # on Windows isn't (yet) supported
    if platform.system() == "Windows":
        diagnostics.fatal("Downloading LLVM on Windows is not supported")

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
            if not should_skip_download(dep):
                get_project_source(dep)
    elif args.build_llvm:
        download_binary()

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
