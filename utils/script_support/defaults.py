#===-------------------------- defaults.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
Default option value definitions.
"""


__all__ = [
    # Command line configurable
    "BUILD_VARIANT",
    "CMAKE_GENERATOR",
    "CXX_STANDARD",
    "ANTHEM_VERSION",
    "DARWIN_DEPLOYMENT_VERSION",
    "UNIX_INSTALL_PREFIX",
    "DARWIN_INSTALL_PREFIX",

    # Constants
]


# Options that can be "configured" by command line options

BUILD_VARIANT = "Debug"
CMAKE_GENERATOR = "Ninja"

CXX_STANDARD = "c++14"

ANTHEM_VERSION = "0.1.0-dev.1"

DARWIN_XCRUN_TOOLCHAIN = "default"
DARWIN_DEPLOYMENT_VERSION = "10.9"

UNIX_INSTALL_PREFIX = "/usr"
DARWIN_INSTALL_PREFIX = "/Applications/Xcode.app/Contents/Developer" \
                        "/Toolchains/XcodeDefault.xctoolchain/usr"

# Options that can only be "configured" by editing this file.
#
# These options are not exposed as command line options on purpose. If you
# need to change any of these, you should do so on trunk or in a branch.
