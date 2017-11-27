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

from . import diagnostics

from .mapping import Mapping

from .products import glfw, llvm

from .products.product_config import \
    anthem_config, product_config, version_config, github_config, asset, \
    SOURCE_ASSET, platform_specific_asset, platform_file_config


__all__ = ["PRODUCT_CONFIG", "PROTOCOL", "GITHUB_API_ENDPOINT"]


PROTOCOL = "https"
GITHUB_API_ENDPOINT = "https://api.github.com/graphql"


ANTHEM_PRODUCT = anthem_config(
    version="0.1.0-dev.1",
    window_name="Unsung Anthem",
    opengl=Mapping(version=Mapping(major=3, minor=2)),
    logger_name="anthem"
)


PRODUCT_CONFIG = Mapping(
    anthem=ANTHEM_PRODUCT,

    llvm=product_config(
        version="4.0.1",
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

    glfw=product_config(
        version="3.2.1",
        name="GLFW3",
        identifier="glfw",
        allow_git_checkout=True,
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
        ),
        post_checkout=glfw.move_checkout_files
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
        version="6.1.0",
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


def apply_versions(build_data):
    """
    Apply the versions from the arguments to the build data.

    build_data -- the build data.
    """
    for product in build_data.products.keys():
        build_data.products[product].version = getattr(
            build_data.args, "{}_version".format(product))
        diagnostics.debug(
            "Set the version {version} to the product {product} in build "
            "data".format(
                version=build_data.products[product].version,
                product=product))

    build_data.products.cmake.version_mapping = \
        build_data.args.cmake_version_mapping

    diagnostics.debug("Set the CMake version mapping to {}".format(
        build_data.products.cmake.version_mapping))
