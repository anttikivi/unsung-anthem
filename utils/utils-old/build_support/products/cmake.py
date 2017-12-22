#===--------------------------- cmake.py ---------------------*- python -*-===#
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
    Resolve the platform which is used in the URL from which CMake is
    downloaded on Linux.

    build_data -- the build data.
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
    Resolve the platform which is used in the URL from which CMake is
    downloaded on Darwin (macOS).

    build_data -- the build data.
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
    Resolve the platform which is used in the URL from which CMake is
    downloaded.

    build_data -- the build data.
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
            product.repr
        )
    )
    return None


def move_release_files(build_data):
    """
    Move the CMake files to the correct location after the download.

    build_data -- the build data.
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
    Download CMake.

    build_data -- the build data.
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

    url = product.url_format.format(
        protocol=build_data.connection_protocol, major_minor=major_minor,
        version=version, platform=cmake_platform, extension=archive_extension
    )
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
    """
    Create the path for the binary of CMake.

    build_data -- the build data.
    """
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


def set_up(build_data):
    """
    Set CMake up for the build.

    build_data -- the build data.
    """
    product = build_data.products.cmake
    build_data.toolchain.cmake = cmake_bin_path(build_data=build_data)
    check_source(product=product)
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
            os.path.join(build_dir, "CMake.app"),
            os.path.join(build_data.install_root, "CMake.app"))
    else:
        shell.copytree(build_dir, build_data.install_root)


def set_toolchain(build_data):
    """
    Set CMake to the toolchain.

    build_data -- the build data.
    """
    build_data.toolchain.cmake = cmake_bin_path(build_data=build_data)
    diagnostics.debug(
        "Set {} to the toolchain from a custom location: {}".format(
            build_data.products.cmake.repr, build_data.toolchain.cmake))
