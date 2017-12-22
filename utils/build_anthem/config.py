#===--------------------------- config.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the configuration of the build.
"""


import os

from build_utils.mapping import Mapping

from build_product import llvm

from build_product.product.product_config import \
    anthem_config, product_config, version_config, github_config, asset, \
    SOURCE_ASSET, platform_specific_asset, platform_file_config


__all__ = ["PRODUCT_CONFIG", "PROTOCOL", "GITHUB_API_ENDPOINT"]


PROTOCOL = "https"
GITHUB_API_ENDPOINT = "https://api.github.com/graphql"


PRODUCT_CONFIG = Mapping(
    anthem=anthem_config(
        version="0.1.0-dev.1",
        window_name="Unsung Anthem",
        opengl=Mapping(version=Mapping(major=3, minor=2)),
        logger_name="anthem"
    ),

    llvm=product_config(
        version="5.0.0",
        name="LLVM",
        identifier="llvm",
        allow_git_checkout=True,
        subproducts=Mapping(
            llvm="llvm", libcxx="libcxx", libcxxabi="libcxxabi", clang="cfe"
        ),
        skip_checkout=llvm.skip_checkout,
        inject_version_info=llvm.inject_version_info,
        git_format="http://llvm.org/git/{key}",
        release_format="{protocol}://releases.llvm.org/{version}/{key}-"
                       "{version}.src.tar.xz",
        binary_format="{protocol}://releases.llvm.org/{version}/clang+llvm-"
                      "{version}-{platform}.tar.xz",

        # The version which is used when the version option of LLVM is set to
        # 'git'.
        git_version="6.0.0svn"
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
        allow_git_checkout=True,
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
        allow_git_checkout=True,
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
        allow_git_checkout=True,
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
        allow_git_checkout=True,
        url_format="{protocol}://www.libsdl.org/release/"
                   "SDL2-{version}.{extension}",
        windows_format="{protocol}://www.libsdl.org/release/"
                       "SDL2-devel-{version}-{type}.{extension}"
    ),

    spdlog=product_config(
        version="0.14.0",
        name="spdlog",
        identifier="spdlog",
        allow_git_checkout=True,
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
        allow_git_checkout=True,
        github_data=github_config(
            owner="Taywee",
            name="args",
            asset_data=SOURCE_ASSET,
            version_prefix=""
        )
    )
)
