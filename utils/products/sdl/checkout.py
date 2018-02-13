#===----------------------------- checkout.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""The support module containing the utilities for SDL checkout."""


import os
import platform

from build_utils import diagnostics, http_stream, shell, workspace

from products import common

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT


def move_files():
    """Move the SDL files to the correct location after the download."""
    product = data.build.products.sdl
    version = product.version
    subdir = "SDL2-{}".format(version)
    shell.rmtree(workspace.source_dir(product=product))

    diagnostics.debug("The name of the {} subdirectory is {}".format(
        product.repr, subdir))

    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp", subdir),
        workspace.source_dir(product=product))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))


def get_dependency():
    """Download SDL."""
    product = data.build.products.sdl
    common.checkout.clean_checkout(product)
    version = product.version
    if platform.system() == "Windows":
        archive_extension = "zip"
        url = product.windows_format.format(
            protocol=data.build.connection_protocol, version=version,
            type="VC", extension=archive_extension)
    else:
        archive_extension = "tar.gz"
        url = product.url_format.format(
            protocol="http", version=version, extension=archive_extension)
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, product.key, "temp",
        "sdl.{}".format(archive_extension))
    http_stream.stream(url=url, destination=destination)
    shell.tar(path=destination, dest=os.path.join(
        ANTHEM_SOURCE_ROOT, product.key, "temp"))
    shell.rm(destination)
    move_files()
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))
