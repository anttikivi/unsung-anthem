#===--------------------------- parser.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing preset-parsing-related helpers.
"""


try:
    # Python 2
    import ConfigParser
except ImportError:
    # Python 3
    import configparser as ConfigParser

import itertools

from build_utils import diagnostics


def _load_preset_files_impl(preset_file_names, defaults=None):
    """
    Load the presets in the preset files.

    preset_file_names -- the names of the files from which the presets are
    loaded.
    defaults -- key-value pair to be default values in the presets.
    """
    if defaults is None:
        defs = {}
    else:
        defs = defaults

    config = ConfigParser.SafeConfigParser(defs, allow_no_value=True)
    if not config.read(preset_file_names):
        diagnostics.fatal("Preset file not found (tried {})".format(
            preset_file_names
        ))
    diagnostics.debug("Loaded preset config from {}".format(preset_file_names))
    return config


_PRESET_PREFIX = "preset: "


def _get_preset_options(config, defaults, preset_name):
    """
    Concatenate the lists of options in the preset.

    config -- the preset file information.
    defaults -- the preset default values.
    preset_name -- the name of the preset.
    parser -- the function used to parse the options.
    """
    def _get_value(option):
        # A hack.
        try:
            value = config.get(section_name, option)
        except ConfigParser.InterpolationMissingOptionError:
            return None
        if not value:
            return ""
        return value

    def parse_option(option):
        """
        Parse single option of the preset and return its value.

        option -- the option to parse.
        """
        value = _get_value(option)
        if option in defaults:
            return None
        if option == "mixin-preset":
            # Mixins are handled separately.
            return None
        elif value == "":
            return "--{}".format(option)
        return "--{}={}".format(option, value)

    def parse_mixins():
        """
        Parse mix-in presets of the preset and return the parsed options from
        the mix-in presets.
        """
        value = _get_value("mixin-preset")
        if "mixin-preset" in defaults:
            return None
        # Split on newlines and filter out empty lines.
        mixins = list(filter(None, [m.strip() for m in value.splitlines()]))
        mixin_opts = (_get_preset_options(config, defaults, m) for m in mixins)
        ret = list(itertools.chain.from_iterable(mixin_opts))
        return ret

    section_name = _PRESET_PREFIX + preset_name
    if section_name not in config.sections():
        return None
    build_script_opts = list(filter(
        None, [parse_option(opt) for opt in config.options(section_name)]
    ))
    mixin_opts = \
        [opt for opt in config.options(section_name) if opt == "mixin-preset"]
    if mixin_opts:
        mixins = list(filter(None, parse_mixins()))
    else:
        mixins = []
    return list(build_script_opts + mixins)


def get_preset_options(defaults, preset_file_names, preset_name):
    """
    Get a list of the options in the preset.

    defaults -- the preset default values.
    preset_file_names -- list of the names of the preset files.
    preset_name -- the name of the preset.
    """
    config = _load_preset_files_impl(preset_file_names, defaults)
    build_script_opts = _get_preset_options(config, defaults, preset_name)
    if not build_script_opts:
        diagnostics.fatal("Preset '{}' wasn't found".format(preset_name))
    return build_script_opts + ["--"]


def get_all_preset_names(preset_file_names):
    """
    Get a list of all presets in the preset files.

    preset_file_names -- list of the names of the preset files.
    """
    config = _load_preset_files_impl(preset_file_names)
    return [name[len(_PRESET_PREFIX):] for name in config.sections()
            if name.startswith(_PRESET_PREFIX)]


def parse_preset_defaults(args):
    """
    Parse the preset default values from the parsed arguments and return them
    as a dictionary.

    args -- the parsed arguments of the program in preset mode.
    """
    # Create a list of tuples as a dict is easily constructed from them.
    defaults = [tuple(x.split("=", 1)) for x in args.preset_defaults_raw]
    return dict(defaults)
