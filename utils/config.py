#===--------------------------- config.py ---------------------*- python -*-===#
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


from build_support import mapping

from build_support.products.llvm import llvm_subproducts

from build_support.products.product_config import \
    product_config, version_config, github_config, asset, SOURCE_ASSET, \
    platform_specific_asset, platform_file_config


ANTHEM_PRODUCT = mapping.Mapping(
    version="0.1.0-dev.1"
)


PRODUCT_CONFIG = mapping.Mapping(
    anthem=ANTHEM_PRODUCT,

    # Git format: http://llvm.org/git/{project}
    # format: {protocol}://releases.llvm.org/{version}/{id}-{version}.src.tar.xz
    llvm=product_config(
        version="4.0.1",
        extra_data=llvm_subproducts("llvm", "libcxx", clang="cfe")
    ),

    # default mirror: nl.mirror.babylon.network/gcc
    # format: {protocol}://{mirror}/releases/gcc-{version}/gcc-{version}.tar.{extension}
    gcc=product_config(
        version="6.4.0"
    ),

    # format: {protocol}://cmake.org/files/v{major_minor}/cmake-{version}-{platform}.{extension}
    cmake=product_config(
        version=version_config(
            major=3,
            minor=9,
            patch=1
        )
    ),

    ninja=product_config(
        version="1.7.2",
        github_data=github_config(
            owner="ninja-build",
            name="ninja",
            version_prefix="v",
            asset_data=platform_specific_asset(
                asset_file="ninja.zip",
                platform_files=platform_file_config(
                    darwin="ninja-mac.zip",
                    windows="ninja-windows.zip",
                    linux="ninja-linux.zip"
                )
            )
        )
    ),

    catch=product_config(
        version="1.9.5",
        github_data=github_config(
            owner="philsquared",
            name="Catch",
            asset_data=asset("catch.hpp"),
            version_prefix="v"
        )
    ),

    # format: "{protocol}://www.libsdl.org/release/SDL2-{version}.{extension}"
    # Windows: "{protocol}://www.libsdl.org/release/SDL2-devel-{version}-{type}.{extension}"
    sdl=product_config(version="2.0.5"),

    glfw=product_config(
        version="3.2.1",
        github_data=github_config(
            owner="glfw",
            name="glfw",
            asset_data=platform_specific_asset(
                asset_file="glfw.zip",
                platform_files=platform_file_config(
                    windows="glfw-3.2.1.bin.WIN32.zip"
                ),
                fallback_file="glfw-3.2.1.zip"
            )
        )
    ),

    spdlog=product_config(
        version="0.13.0",
        github_data=github_config(
            owner="gabime",
            name="spdlog",
            asset_data=SOURCE_ASSET,
            version_prefix="Version "
        )
    ),

    cat=product_config(
        version="1.3",
        github_data=github_config(
            owner="awgn",
            name="cat",
            asset_data=SOURCE_ASSET,
            version_prefix="v"
        )
    )
)
