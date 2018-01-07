#===--------------------------- config.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the configuration of the build.
"""


import os

from build_utils.mapping import Mapping

from products import llvm

from .product_config import \
    product_config, \
    version_config, \
    github_config, \
    asset, \
    SOURCE_ASSET, \
    platform_specific_asset, \
    platform_file_config


__all__ = ["PRODUCT_CONFIG", "PROTOCOL", "GITHUB_API_V4_ENDPOINT"]


PROTOCOL = "https"
GITHUB_API_V4_ENDPOINT = "https://api.github.com/graphql"


PRODUCT_CONFIG = Mapping(
    llvm=product_config(
        version="5.0.1",
        name="LLVM",
        identifier="llvm",
        subproducts=Mapping(
            llvm="llvm", libcxx="libcxx", libcxxabi="libcxxabi", clang="cfe"
        ),
        skip_checkout=True,
        inject_version_info=llvm.checkout.inject_version_info,
        source_format="{protocol}://releases.llvm.org/{version}/{key}-"
                      "{version}.src.tar.xz",
        binary_format="{protocol}://releases.llvm.org/{version}/clang+llvm-"
                      "{version}-{platform}.tar.xz",
        binary_platforms=Mapping(
            ubuntu="linux-gnu-ubuntu-16.04",
            darwin="apple-darwin"
        )
    ),

    cmake=product_config(
        version=version_config(
            major=3,
            minor=8,
            patch=2
        ),
        name="CMake",
        identifier="cmake",
        version_format="MAJOR.MINOR.PATCH(.MINOR_PATCH)",
        url_format="{protocol}://cmake.org/files/v{major_minor}/cmake-"
                   "{version}-{platform}.{extension}"
    ),

    ninja=product_config(
        version="1.7.2",
        name="Ninja",
        identifier="ninja",
        github_data=github_config(
            owner="ninja-build",
            name="ninja",
            version_prefix="v",
            asset_data=platform_specific_asset(
                asset_file="ninja.zip",
                platform_files=platform_file_config(
                    darwin="ninja-mac.zip",
                    windows="ninja-win.zip",
                    linux="ninja-linux.zip"
                )
            )
        )
    ),

    glad=product_config(
        version="0.1.14a0",
        name="glad",
        identifier="glad",
        github_data=github_config(
            owner="Dav1dde",
            name="glad",
            asset_data=SOURCE_ASSET,
            version_prefix="v"
        )
    ),

    catch=product_config(
        version="2.0.1",
        name="Catch",
        identifier="catch",
        github_data=github_config(
            owner="catchorg",
            name="Catch2",
            asset_data=asset("catch.hpp"),
            version_prefix="v"
        )
    ),

    sdl=product_config(
        version="2.0.7",
        name="SDL2",
        identifier="sdl",
        url_format="{protocol}://www.libsdl.org/release/"
                   "SDL2-{version}.{extension}",
        windows_format="{protocol}://www.libsdl.org/release/"
                       "SDL2-devel-{version}-{type}.{extension}"
    ),

    spdlog=product_config(
        version="0.14.0",
        name="spdlog",
        identifier="spdlog",
        build_subdir=os.path.join("include", "spdlog"),
        github_data=github_config(
            owner="gabime",
            name="spdlog",
            asset_data=SOURCE_ASSET,
            version_prefix="Version "
        )
    ),

    args=product_config(
        version="6.2.0",
        name="args",
        identifier="args",
        github_data=github_config(
            owner="Taywee",
            name="args",
            asset_data=SOURCE_ASSET,
            version_prefix=""
        )
    )
)
