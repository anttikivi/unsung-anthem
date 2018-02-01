#===----------------------------- checkout.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for CMake checkout.
"""


import os
import platform

from build_utils import diagnostics, http_stream, shell, workspace

from products import common

from script_support import data

from script_support.variables import ANTHEM_SOURCE_ROOT

from . import platforms


def move_files():
    """
    Move the CMake files to the correct location after the download.
    """
    product = data.build.products.cmake
    version = product.version
    cmake_platform = platforms.resolve()
    subdir = "cmake-{}-{}".format(version, cmake_platform)
    shell.rmtree(workspace.source_dir(product=product))

    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))

    if platform.system() == "Darwin":
        cmake_app = os.listdir(os.path.join(
            ANTHEM_SOURCE_ROOT, product.key, "temp", subdir))[0]

        shell.copytree(
            os.path.join(
                ANTHEM_SOURCE_ROOT, product.key, "temp", subdir, cmake_app
            ),
            os.path.join(workspace.source_dir(product=product), "CMake.app")
        )
    else:
        shell.copytree(
            os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp", subdir),
            workspace.source_dir(product=product)
        )
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))


def get_dependency():
    """
    Download CMake.
    """
    product = data.build.products.cmake

    common.checkout.clean_checkout(product)

    version = product.version

    version_mapping = product.version_mapping
    major_minor = "{}.{}".format(version_mapping.major, version_mapping.minor)

    cmake_platform = platforms.resolve()

    if platform.system() == "Windows":
        archive_extension = "zip"
    else:
        archive_extension = "tar.gz"

    url = product.url_format.format(
        protocol=data.build.connection_protocol,
        major_minor=major_minor,
        version=version,
        platform=cmake_platform,
        extension=archive_extension
    )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, product.key, "temp", "cmake.{}".format(
            archive_extension
        )
    )

    http_stream.stream(url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))
    shell.rm(destination)
    move_files()

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, product.key, "temp"))
