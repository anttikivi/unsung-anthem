#===--------------------------- cmake.py ----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the CMake product helpers.
"""


import os
import platform
import tarfile
import zipfile

import requests

from .. import diagnostics, shell

from ..variables import ANTHEM_SOURCE_ROOT


def resolve_linux_platform(build_data):
    """
    """
    version_mapping = build_data.products.cmake.version_mapping
    # Starting at CMake 3.1.0 'Linux-x86_64' variant is available, before that
    # the only option is 'Linux-i386'.
    if version_mapping.major < 3:
        return "Linux-i386"
    if version_mapping.minor < 1:
        return "Linux-i386"
    return "Linux-x86_64"


def resolve_darwin_platform(build_data):
    """
    """
    version_mapping = build_data.products.cmake.version_mapping
    # Starting at CMake 3.1.1 'Darwin-x86_64' variant is available, before that
    # the only option is 'Darwin-universal'.
    if version_mapping.major < 3:
        return "Darwin-universal"
    if version_mapping.minor <= 1:
        if version_mapping.patch < 1:
            return "Darwin-universal"
        return "Darwin-x86_64"
    return "Darwin-x86_64"


def resolve_platform(build_data):
    """
    """
    product = build_data.products.cmake
    if platform.system() == "Windows":
        return "win32-x86"
    elif platform.system() == "Linux":
        return resolve_linux_platform(build_data)
    elif platform.system() == "Darwin":
        return resolve_darwin_platform(build_data)

    diagnostics.warn(
        "{} will not be downloaded as the platform is not supported".format(
            product.repr))
    return None


def move_release_files(build_data):
    """
    """
    version = build_data.products.cmake.version
    cmake_platform = resolve_platform(build_data)
    subdir = "cmake-{}-{}".format(version, cmake_platform)
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", version))

    if platform.system() == "Darwin":
        cmake_app = os.listdir(os.path.join(
            ANTHEM_SOURCE_ROOT, "cmake", "temp", subdir))[0]

        shell.copytree(
            os.path.join(
                ANTHEM_SOURCE_ROOT, "cmake", "temp", subdir, cmake_app),
            os.path.join(ANTHEM_SOURCE_ROOT, "cmake", version, "CMake.app"))
    else:
        shell.copytree(
            os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp", subdir),
            os.path.join(ANTHEM_SOURCE_ROOT, "cmake", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))


def get_dependency(build_data):
    """
    """
    args = build_data.args
    product = build_data.products.cmake
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))

    version_mapping = product.version_mapping
    major_minor = "{}.{}".format(version_mapping.major, version_mapping.minor)

    cmake_platform = resolve_platform(build_data)

    if platform.system() == "Windows":
        archive_extension = "zip"
    else:
        archive_extension = "tar.gz"

    # TODO: protocol=build_data.connection_protocol
    url = product.url_format.format(
        protocol="http", major_minor=major_minor, version=version,
        platform=cmake_platform, extension=archive_extension)

    diagnostics.debug("Streaming an asset from {}".format(url))

    responce = requests.get(url=url, stream=True)

    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "cmake", "temp", "cmake.{}".format(
            archive_extension))

    with open(destination, "wb") as destination_file:
        for chunk in responce.iter_content(chunk_size=1024):
            if chunk:
                destination_file.write(chunk)

    diagnostics.debug_ok(
        "Finished streaming an asset to {}".format(destination))

    if archive_extension == "zip":
        with zipfile.ZipFile(destination, "r") as archive:
            archive.extractall(
                os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))
    else:
        with tarfile.open(destination) as archive:
            archive.extractall(
                os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))
    shell.rm(destination)
    move_release_files(build_data)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))
