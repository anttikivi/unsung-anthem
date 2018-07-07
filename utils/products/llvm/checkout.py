#===----------------------------- checkout.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for LLVM checkout."""


import os
import platform

from build_utils import diagnostics, http_stream, shell, workspace

from products import common

from script_support import data


def resolve_platform():
    """Resolve the platform which is used in the LLVM filename."""
    product = data.build.products.llvm
    if platform.system() == "Linux":
        return "x86_64-linux-gnu-ubuntu-14.04"
    elif platform.system() == "Darwin":
        return "x86_64-apple-darwin"

    diagnostics.warn(
        "{} will not be downloaded as the platform is not supported".format(
            product.repr))
    return None


def move_files():
    """Move the LLVM files to the correct location after the download."""
    product = data.build.products.llvm
    version = product.version
    llvm_platform = resolve_platform()
    subdir = "clang+llvm-{}-{}".format(version, llvm_platform)
    shell.rmtree(workspace.source_dir(product=product))
    diagnostics.debug("The name of the {} subdirectory is {}".format(
        product.repr, subdir))

    shell.copytree(
        os.path.join(workspace.temp_dir(product=product), subdir),
        workspace.source_dir(product=product))
    shell.rmtree(workspace.temp_dir(product=product))


def get_dependency():
    """Download LLVM."""
    product = data.build.products.llvm
    common.checkout.clean_checkout(product)
    version = product.version
    llvm_platform = resolve_platform()
    archive_extension = "tar.xz"
    url = product.url_format.format(
        protocol=data.build.connection_protocol, version=version,
        platform=llvm_platform, extension=archive_extension)
    destination = os.path.join(
        workspace.temp_dir(product=product),
        "llvm.{}".format(archive_extension))
    http_stream.stream(url=url, destination=destination)
    shell.tar(path=destination, dest=workspace.temp_dir(product=product))
    shell.rm(destination)
    move_files()
    shell.rmtree(workspace.temp_dir(product=product))
