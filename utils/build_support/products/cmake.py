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

from .product import binary_exists, check_source

from .. import diagnostics, shell, workspace

from ..httpstream import stream_file

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
    product = build_data.products.cmake
    version = product.version
    cmake_platform = resolve_platform(build_data)
    subdir = "cmake-{}-{}".format(version, cmake_platform)
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", version))

    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))

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
        protocol="https", major_minor=major_minor, version=version,
        platform=cmake_platform, extension=archive_extension)
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "cmake", "temp", "cmake.{}".format(
            archive_extension)
    )

    stream_file(build_data=build_data, url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))
    shell.rm(destination)
    move_release_files(build_data)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "cmake", "temp"))


def cmake_bin_path(build_data):
    if platform.system() == "Windows":
        return os.path.join(build_data.install_root, "bin", "cmake.exe")
    elif platform.system() == "Linux":
        return os.path.join(build_data.install_root, "bin", "cmake")
    elif platform.system() == "Darwin":
        return os.path.join(
            build_data.install_root, "CMake.app", "Contents", "bin", "cmake")
    diagnostics.fatal(
        "{} is not supported for {}".format(
            platform.system(), build_data.products.cmake.repr))


def do_build(build_data):
    product = build_data.products.cmake
    bin_path = cmake_bin_path(build_data=build_data)
    build_dir = workspace.build_dir(
        build_data=build_data, product=product, target="build"
    )
    if binary_exists(
            build_data=build_data, product=product, path=bin_path,
            target="build"):
        return
    source_dir = workspace.source_dir(product=product)

    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    if platform.system() == "Darwin":
        shell.copytree(
            os.path.join(source_dir, "CMake.app"),
            os.path.join(build_data.install_root, "CMake.app"))
    else:
        shell.copytree(source_dir, build_data.install_root)


def set_up(build_data):
    """
    """
    product = build_data.products.cmake
    check_source(product=product)
    do_build(build_data=build_data)
    build_data.toolchain.cmake = cmake_bin_path(build_data=build_data)
