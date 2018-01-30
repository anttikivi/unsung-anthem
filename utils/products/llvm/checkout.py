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

from build_utils import diagnostics, http_stream, shell, workspace

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT, VERSIONS_FILE

from . import libcxx


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
            subnode = version_node[key]
            if subnode["version"] == data.build.products.llvm.version \
                    and data.build.host_target in subnode["targets"]:
                diagnostics.debug(
                    "{} should not be re-downloaded, skipping".format(key)
                )
                return True
    return False


def _remove_old_checkout(key):
    """
    Remove the old checkout of the given LLVM subproject.

    key -- the name of the subproject.
    """
    product = data.build.products.llvm
    shell.rmtree(workspace.source_dir(product=product, subproject=key))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))


def move_project_files(key, subdir):
    """
    Move the LLVM subproduct files to the correct location after the download.

    key -- the name of the subproject.
    """
    product = data.build.products.llvm
    version = product.version

    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, key, "temp", subdir),
        workspace.source_dir(product=product, subproject=key)
    )

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))


def _get_project_source(key):
    """
    Download the given LLVM subproject.

    key -- the name of the subproject.
    """
    diagnostics.debug("Downloading LLVM subproject {}".format(key))

    product = data.build.products.llvm
    version = product.version

    _remove_old_checkout(key)

    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))

    url = product.source_format.format(
        protocol=data.build.connection_protocol,
        version=version,
        key=product.subprojects[key]
    )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, key, "temp", "{}.tar.xz".format(key)
    )
    http_stream.stream(url=url, destination=destination)
    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, key, "temp")
    )
    subdir = "{}-{}.src".format(product.subprojects[key], version)
    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir)
    )
    # FIXME: This is bad, this is hardcoded.
    if key == "libcxx":
        libcxx.checkout.remove_bad_symlink(subdir)
    shell.rm(destination)
    move_project_files(key=key, subdir=subdir)


def _download_binary():
    """
    Download the pre-built LLVM binary.
    """
    product = data.build.products.llvm
    version = product.version
    key = product.identifier

    _remove_old_checkout(key)

    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))

    # TODO
    sys = platform.system()
    if sys == "Linux":
        machine = "{}-{}".format("x86_64", product.binary_platforms.ubuntu)
    else:
        machine = "{}-{}".format("x86_64", product.binary_platforms.darwin)
    url = product.binary_format.format(
        protocol=data.build.connection_protocol,
        version=version,
        platform=machine
    )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, key, "temp", "{}.tar.xz".format(key)
    )

    http_stream.stream(url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, key, "temp")
    )

    subdir_format = "clang+llvm-{version}-{platform}"
    # TODO
    if sys == "Darwin":
        subdir_format = "clang+llvm-{version}-final-{platform}"

    subdir = subdir_format.format(version=version, platform=machine)
    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir)
    )
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
    key = product.identifier

    llvm_deps = None

    if args.build_libcxx:
        llvm_deps = ["llvm", "libcxx", "libcxxabi"]
    elif args.build_llvm:
        llvm_deps = list(product.subprojects.keys())

    if args.source_llvm or args.build_libcxx:
        for dep in llvm_deps:
            if not should_skip_download(dep):
                shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, dep, "temp"))
                shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, dep, "temp"))
                # TODO
                _get_project_source(dep)
    elif args.build_llvm and not should_skip_download("llvm"):
        shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
        shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))
        _download_binary()

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, key, "temp"))


def inject_version_info(versions):
    """
    Add the LLVM version info to the checkout version info.

    versions -- the version info dictionary of the checkout.
    """
    product = data.build.products.llvm
    args = data.build.args
    version = product.version
    target = data.build.host_target
    version_info = None
    if args.build_libcxx:
        version_info = {
            "llvm": {"version": version, "targets": [target]},
            "clang": {"version": 0, "targets": 0},
            "libcxx": {"version": version, "targets": [target]},
            "libcxxabi": {"version": version, "targets": [target]}
        }
    elif args.build_llvm:
        version_info = {
            "llvm": {"version": version, "targets": [target]},
            "clang": {"version": version, "targets": [target]},
            "libcxx": {"version": version, "targets": [target]},
            "libcxxabi": {"version": version, "targets": [target]}
        }
    versions["llvm"] = version_info
