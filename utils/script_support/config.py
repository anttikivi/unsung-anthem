#===------------------------------ config.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the configuration of the build.
"""


import os
import platform

from build_utils.mapping import Mapping

from .product_config import \
    product_config, \
    version_config, \
    github_config, \
    asset, \
    SOURCE_ASSET, \
    platform_specific_asset, \
    platform_file_config, \
    ode_config, \
    anthem_config


__all__ = ["PRODUCT_CONFIG", "PROTOCOL", "GITHUB_API_V4_ENDPOINT"]


PROTOCOL = "https"
GITHUB_API_V4_ENDPOINT = "https://api.github.com/graphql"


PRODUCT_CONFIG = Mapping(
    anthem=anthem_config(
        version="0.1.0-dev.1",
        window_name="Unsung Anthem",
        logger_name="anthem",
        is_tool=False,
        is_source=True
    ),

    catch2=product_config(
        version="2.1.1",
        name="Catch2",
        key="catch2",
        is_tool=False,
        is_source=True,
        github_data=github_config(
            owner="catchorg",
            name="Catch2",
            asset_data=asset("catch.hpp"),
            version_prefix="v"
        )
    ),

    clara=product_config(
        version="1.1.1",
        name="Clara",
        key="clara",
        is_tool=False,
        is_source=True,
        github_data=github_config(
            owner="catchorg",
            name="Clara",
            asset_data=asset("clara.hpp"),
            version_prefix="v"
        )
    ),

    cmake=product_config(
        version=version_config(
            major=3,
            minor=8,
            patch=2
        ),
        name="CMake",
        key="cmake",
        is_tool=True,
        is_source=False,
        url_format="{protocol}://cmake.org/files/v{major_minor}/cmake-"
                   "{version}-{platform}.{extension}"
    ),

    glad=product_config(
        version="0.1.16a0",
        name="glad",
        key="glad",
        is_tool=False,
        is_source=True,
        github_data=github_config(
            owner="Dav1dde",
            name="glad",
            asset_data=SOURCE_ASSET,
            version_prefix="v"
        )
    ),

    hayai=product_config(
        version="1.0.1",
        name="hayai",
        key="hayai",
        is_tool=False,
        is_source=True,
        github_data=github_config(
            owner="nickbruun",
            name="hayai",
            asset_data=SOURCE_ASSET,
            version_prefix="v"
        )
    ),

    lua=product_config(
        version="5.3.4",
        name="Lua",
        key="lua",
        is_tool=False,
        is_source=True,
        url_format="{protocol}://www.lua.org/ftp/lua-{version}.tar.gz"
    ),

    ninja=product_config(
        version="1.8.2",
        name="Ninja",
        key="ninja",
        is_tool=True,
        is_source=False,
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

    ode=ode_config(
        version="0.1.0-dev.1",
        opengl=Mapping(version=Mapping(major=3, minor=2)),
        logger_name="ode",
        is_tool=False,
        is_source=True
    ),

    sdl=product_config(
        version="2.0.7",
        name="Simple DirectMedia Layer",
        key="sdl",
        is_tool=False,
        is_source=not platform.system() == "Windows",
        url_format="{protocol}://www.libsdl.org/release/"
                   "SDL2-{version}.{extension}",
        windows_format="{protocol}://www.libsdl.org/release/"
                       "SDL2-devel-{version}-{type}.{extension}"
    ),

    spdlog=product_config(
        version="0.16.3",
        name="spdlog",
        key="spdlog",
        is_tool=False,
        is_source=True,
        build_subdir=os.path.join("include", "spdlog"),
        github_data=github_config(
            owner="gabime",
            name="spdlog",
            asset_data=SOURCE_ASSET,
            version_prefix="Version "
        )
    )
)
