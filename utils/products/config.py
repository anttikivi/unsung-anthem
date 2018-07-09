#===------------------------------ config.py ------------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""Product option value definitions."""


import os
import platform

from build_utils.mapping import Mapping

from script_support.product_mapping import ode_anthem_config, product_config, \
    github_config, SOURCE_ASSET, asset, version_config, \
    platform_specific_asset, platform_file_config


ANTHEM_VERSION = "0.1.0-dev.1"
ANTHEM_NAME = "Unsung Anthem"
ANTHEM_KEY = "anthem"
ANTHEM_WINDOW_NAME = "Unsung Anthem"
ANTHEM_LOGGER_NAME = "anthem"


BENCHMARK_VERSION = "1.4.1"


CLARA_VERSION = "1.1.4"


CMAKE_MAJOR_VERSION = 3
CMAKE_MINOR_VERSION = 11
CMAKE_PATCH_VERSION = 1


GLAD_VERSION = "0.1.24"


GOOGLETEST_VERSION = "1.8.0"


LLVM_VERSION = "6.0.0"


LUA_VERSION = "5.3.4"


NINJA_VERSION = "1.8.2"


ODE_VERSION = "0.1.0-dev.1"
ODE_NAME = "Obliging Ode"
ODE_KEY = "ode"
ODE_OPENGL_MAJOR_VERSION = 3
ODE_OPENGL_MINOR_VERSION = 2
ODE_LOGGER_NAME = "ode"


SDL_VERSION = "2.0.8"


SPDLOG_VERSION = "0.17.0"


STB_IMAGE_VERSION = "2.19"


PRODUCT_CONFIG = Mapping(
    anthem=ode_anthem_config(
        version=ANTHEM_VERSION,
        name=ANTHEM_NAME,
        key=ANTHEM_KEY,
        window_name=ANTHEM_WINDOW_NAME,
        logger_name=ANTHEM_LOGGER_NAME,
        is_tool=False,
        is_source=True
    ),

    benchmark=product_config(
        version=BENCHMARK_VERSION,
        name="benchmark",
        key="benchmark",
        is_tool=False,
        is_source=True,
        github_data=github_config(
            owner="google",
            name="benchmark",
            asset_data=SOURCE_ASSET,
            version_prefix="v"
        )
    ),

    clara=product_config(
        version=CLARA_VERSION,
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
            major=CMAKE_MAJOR_VERSION,
            minor=CMAKE_MINOR_VERSION,
            patch=CMAKE_PATCH_VERSION
        ),
        name="CMake",
        key="cmake",
        is_tool=True,
        is_source=False,
        url_format="{protocol}://cmake.org/files/v{major_minor}/cmake-"
                   "{version}-{platform}.{extension}"
    ),

    glad=product_config(
        version=GLAD_VERSION,
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

    googletest=product_config(
        version=GOOGLETEST_VERSION,
        name="Google Test",
        key="googletest",
        is_tool=False,
        is_source=True,
        github_data=github_config(
            owner="google",
            name="googletest",
            asset_data=SOURCE_ASSET,
            version_prefix="release-"
        )
    ),

    llvm=product_config(
        version=LLVM_VERSION,
        name="Low Level Virtual Machine",
        key="llvm",
        is_tool=True,
        is_source=False,
        url_format="{protocol}://releases.llvm.org/{version}/"
                   "clang+llvm-{version}-{platform}.{extension}"
    ),

    lua=product_config(
        version=LUA_VERSION,
        name="Lua",
        key="lua",
        is_tool=False,
        is_source=True,
        url_format="{protocol}://www.lua.org/ftp/lua-{version}.tar.gz"
    ),

    ninja=product_config(
        version=NINJA_VERSION,
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

    ode=ode_anthem_config(
        version=ODE_VERSION,
        name=ODE_NAME,
        key=ODE_KEY,
        opengl=Mapping(version=Mapping(
            major=ODE_OPENGL_MAJOR_VERSION,
            minor=ODE_OPENGL_MINOR_VERSION)),
        logger_name=ODE_LOGGER_NAME,
        is_tool=False,
        is_source=True
    ),

    sdl=product_config(
        version=SDL_VERSION,
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
        version=SPDLOG_VERSION,
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
    ),

    stb=product_config(
        version=STB_IMAGE_VERSION,
        name="stb_image",
        key="stb",
        is_tool=False,
        is_source=True,
        master=True,
        github_data=github_config(
            owner="nothings",
            name="stb",
            asset_data=SOURCE_ASSET
        )
    )
)
