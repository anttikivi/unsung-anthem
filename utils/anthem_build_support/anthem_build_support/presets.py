# anthem_build_support/presets.py ------------------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

try:
    # Python 2
    import ConfigParser
except ImportError:
    # Python 3
    import configparser as ConfigParser

import diagnostics


def _load_preset_files_impl(preset_file_names, substitutions={}):
    config = ConfigParser.SafeConfigParser(substitutions, allow_no_value=True)
    if config.read(preset_file_names) == []:
        diagnostics.fatal("preset file not found (tried "
                          + str(preset_file_names)
                          + ")")
    return config


_PRESET_PREFIX = "preset: "


def get_all_preset_names(preset_file_names):
    config = _load_preset_files_impl(preset_file_names)
    return [name[len(_PRESET_PREFIX):] for name in config.sections() if
            name.startswith(_PRESET_PREFIX)]
