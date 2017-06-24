# anthem_build_support/variables.py ------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

import os


def _get_default_source_root():
    # Are we in an Unsung Anthem checkout? Start from this file and check its
    # parent directories.
    #
    # $ANTHEM_SOURCE_ROOT/unsung-anthem/utils/anthem_build_support/anthem_build_support/variables.py
    utils_path = os.path.dirname(os.path.dirname(os.path.dirname(__file__)))
    (anthem_path, parent_dirname) = os.path.split(utils_path)

    if parent_dirname != "utils":
        return ""

    if not os.path.exists(os.path.join(anthem_path, 'CMakeLists.txt')):
        return ""

    return os.path.dirname(anthem_path)


# Set ANTHEM_SOURCE_ROOT in your environment to control where the sources are
# found.
ANTHEM_SOURCE_ROOT = os.environ.get("ANTHEM_SOURCE_ROOT",
                                    _get_default_source_root())
