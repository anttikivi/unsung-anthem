#===----------------------------- checkout.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

"""The support module containing the utilities for CMake checkout."""


import os
import platform

from build_utils import diagnostics, http_stream, shell, workspace

from products import common

from script_support import data


def _resolve_linux():
    """
    Resolve the platform which is used in the URL from which CMake is
    downloaded on Linux.
    """
    version_mapping = data.build.products.cmake.version_mapping
    # Starting at CMake 3.1.0 'Linux-x86_64' variant is available, before that
    # the only option is 'Linux-i386'.
    if version_mapping.major < 3:
        return "Linux-i386"
    if version_mapping.minor < 1:
        return "Linux-i386"
    return "Linux-x86_64"


def _resolve_darwin():
    """
    Resolve the platform which is used in the URL from which CMake is
    downloaded on Darwin (macOS).
    """
    version_mapping = data.build.products.cmake.version_mapping
    # Starting at CMake 3.1.1 'Darwin-x86_64' variant is available, before that
    # the only option is 'Darwin-universal'.
    if version_mapping.major < 3:
        return "Darwin-universal"
    if version_mapping.minor <= 1:
        if version_mapping.patch < 1:
            return "Darwin-universal"
        return "Darwin-x86_64"
    return "Darwin-x86_64"


def resolve_platform():
    """
    Resolve the platform which is used in the URL from which CMake is
    downloaded.
    """
    product = data.build.products.cmake
    if platform.system() == "Windows":
        return "win32-x86"
    elif platform.system() == "Linux":
        return _resolve_linux()
    elif platform.system() == "Darwin":
        return _resolve_darwin()

    diagnostics.warn(
        "{} will not be downloaded as the platform is not "
        "supported".format(product.repr))
    return None


def move_files():
    """Move the CMake files to the correct location after the download."""
    product = data.build.products.cmake
    version = product.version
    cmake_platform = resolve_platform()
    subdir = "cmake-{}-{}".format(version, cmake_platform)
    shell.rmtree(workspace.source_dir(product=product))
    diagnostics.debug("The name of the {} subdirectory is {}".format(
        product.repr, subdir))

    if platform.system() == "Darwin":
        cmake_app = os.listdir(os.path.join(
            workspace.temp_dir(product=product), subdir))[0]

        shell.copytree(
            os.path.join(
                workspace.temp_dir(product=product), subdir, cmake_app),
            os.path.join(workspace.source_dir(product=product), "CMake.app"))
    else:
        shell.copytree(
            os.path.join(workspace.temp_dir(product=product), subdir),
            workspace.source_dir(product=product))
    shell.rmtree(workspace.temp_dir(product=product))


def get_dependency():
    """Download CMake."""
    product = data.build.products.cmake
    common.checkout.clean_checkout(product)
    version = product.version
    version_mapping = product.version_mapping
    major_minor = "{}.{}".format(version_mapping.major, version_mapping.minor)
    cmake_platform = resolve_platform()
    if platform.system() == "Windows":
        archive_extension = "zip"
    else:
        archive_extension = "tar.gz"
    url = product.url_format.format(
        protocol=data.build.connection_protocol, major_minor=major_minor,
        version=version, platform=cmake_platform, extension=archive_extension)
    destination = os.path.join(
        workspace.temp_dir(product=product),
        "cmake.{}".format(archive_extension))
    http_stream.stream(url=url, destination=destination)
    shell.tar(path=destination, dest=workspace.temp_dir(product=product))
    shell.rm(destination)
    move_files()
    shell.rmtree(workspace.temp_dir(product=product))
