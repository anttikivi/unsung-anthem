#===------------------------- variables.py -------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing build variables.
"""


import os


# $HOME is got as an environment variable so it is set to the value it is
# expected to have.
HOME = os.environ.get("HOME", "/")


def _anthem_path():
    """
    Resolve the root directory of the Unsung Anthem checkout. This functions is
    used only by the other utility functions.
    """

    # Get the parent directory of this file for checking if this file is
    # located in an Unsung Anthem checkout.
    #
    # $ANTHEM_SOURCE_ROOT/unsung-anthem/utils/build_support/variables.py
    utils_path = os.path.dirname(os.path.dirname(__file__))

    # Split the path as the first part of the 'utils_path' is presumably the
    # Unsung Anthem checkout.
    (anthem_path, parent_dirname) = os.path.split(utils_path)

    if parent_dirname != "utils":
        return ""

    # The checkout has to have CMake Listfile.
    if not os.path.exists(os.path.join(anthem_path, 'CMakeLists.txt')):
        return ""

    return anthem_path


def _get_default_source_root():
    """
    Resolve the root directory of Unsung Anthem and the dependency
    repositories.
    """
    return os.path.dirname(_anthem_path())


# $ANTHEM_SOURCE_ROOT is resolved from the path of this file if the environment
# variable is not set.
ANTHEM_SOURCE_ROOT = os.environ.get(
    "ANTHEM_SOURCE_ROOT", _get_default_source_root())


# $ANTHEM_BUILD_ROOT is resolved from $ANTHEM_SOURCE_ROOT if the environment
# variable is not set.
ANTHEM_BUILD_ROOT = os.environ.get(
    "ANTHEM_BUILD_ROOT", os.path.join(ANTHEM_SOURCE_ROOT, "build"))


def _get_default_anthem_repo_name():
    """
    Resolve the name of the Unsung Anthem checkout directory.
    """
    # Split the path of the checkout directory as the latter part of it is the
    # filename of the checkout directory.
    (_, anthem_repo_name) = os.path.split(_anthem_path())
    return anthem_repo_name


# $ANTHEM_REPO_NAME is resolved from the path of this file if the environment
# variable is not set.
ANTHEM_REPO_NAME = os.environ.get(
    "ANTHEM_REPO_NAME", _get_default_anthem_repo_name())


SCRIPT_DIR = os.path.join(ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME, "utils")


VERSIONS_FILE = os.path.join(ANTHEM_SOURCE_ROOT, "versions")
