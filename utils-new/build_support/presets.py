#===--------------------------- presets.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing preset-related helpers.
"""


try:
    # Python 2
    import ConfigParser
except ImportError:
    # Python 3
    import configparser as ConfigParser


from . import diagnostics


def _load_preset_files_impl(preset_file_names, substitutions=None):
    """
    Load the presets in the preset files.

    preset_file_names -- the names of the files from which the presets are loaded.
    substitutions -- key-value pair to be substituted in the presets.
    """

    if substitutions is None:
        subs = {}
    else:
        subs = substitutions

    config = ConfigParser.SafeConfigParser(subs, allow_no_value=True)
    if not config.read(preset_file_names):
        diagnostics.fatal("preset file not found (tried "
                          + str(preset_file_names)
                          + ")")
    return config


_PRESET_PREFIX = "preset: "


def get_all_preset_names(preset_file_names):
    """
    Get a list of all presets in the preset files.

    preset_file_names -- list of the names of the preset files.
    """
    config = _load_preset_files_impl(preset_file_names)
    return [name[len(_PRESET_PREFIX):] for name in config.sections()
            if name.startswith(_PRESET_PREFIX)]
