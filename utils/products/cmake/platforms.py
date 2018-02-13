#===----------------------------- platform.py ---------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the utilities for CMake platform.
"""


import platform

from build_utils import diagnostics

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


def resolve():
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
