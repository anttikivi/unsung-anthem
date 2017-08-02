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

import itertools

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
    diagnostics.debug("loaded preset config from " + str(preset_file_names))
    return config


_PRESET_PREFIX = "preset: "


def _get_preset_options_impl(config, substitutions, preset_name):
    """
    Concatenate the lists of options in the preset.

    config -- the preset file information.
    substitutions -- the preset value substitutions.
    preset_name -- the name of the preset.
    parser -- the function used to parse the options.
    """

    def _get_value(option):
        # A dirty hack.
        try:
            value = config.get(section_name, option)
        except ConfigParser.InterpolationMissingOptionError:
            return None

        if not value:
            return ""

        diagnostics.debug("value of option " + option + " in presets is " + value)

        return value

    def _parse_option(option):
        value = _get_value(option)

        if option in substitutions:
            return None

        if option == "mixin-preset":
            # Mixins are handled separately.
            return None
        elif value == "":
            return "--" + option

        return "--" + option + "=" + value

    def _parse_mixins(option):
        value = _get_value(option)

        if option in substitutions:
            return None

        if option == "mixin-preset":
            # Split on newlines and filter out empty lines.
            mixins = filter(None, [m.strip() for m in value.splitlines()])
            mixin_opts = [_get_preset_options_impl(config, substitutions, m)
                          for m in mixins]
            return itertools.chain.from_iterable(mixin_opts)

        return None

    section_name = _PRESET_PREFIX + preset_name

    if section_name not in config.sections():
        return None

    build_script_opts = filter(None, [_parse_option(opt)
                                      for opt in config.options(section_name)])
    mixins = filter(None, [_parse_mixins(opt)
                           for opt in config.options(section_name)])

    return build_script_opts + mixins


def _get_missing_options_impl(config, substitutions, preset_name):
    """
    Concatenate the lists of options which are specified in the substitutions
    but are not in the preset.

    config -- the preset file information.
    substitutions -- the preset value substitutions.
    preset_name -- the name of the preset.
    parser -- the function used to parse the options.
    """

    def _parse_missing_opts(option):
        # A dirty hack.
        try:
            _ = config.get(section_name, option)
        except ConfigParser.InterpolationMissingOptionError as err:
            # err.reference contains the correctly formatted option.
            return err.reference

        return None

    def _parse_mixins(option):
        value = _get_value(option)

        if option in substitutions:
            return None

        if option == "mixin-preset":
            # Split on newlines and filter out empty lines.
            mixins = filter(None, [m.strip() for m in value.splitlines()])
            mixin_opts = [_get_preset_options_impl(config, substitutions, m)
                          for m in mixins]
            return itertools.chain.from_iterable(mixin_opts)

        return None

    section_name = _PRESET_PREFIX + preset_name

    if section_name not in config.sections():
        return None

    missing_opts = filter(None, [_parse_missing_opts(opt)
                                 for opt in config.options(section_name)])
    mixins = filter(None, [_parse_mixins(opt)
                           for opt in config.options(section_name)])

    return missing_opts + mixins


def get_preset_options(substitutions, preset_file_names, preset_name):
    """
    Get a list of the options in the preset.

    substitutions -- the preset value substitutions.
    preset_file_names -- list of the names of the preset files.
    preset_name -- the name of the preset.
    """
    def _get_opts(config, substitutions, preset_name):
        return (_get_preset_options_impl(config, substitutions, preset_name),
                _get_missing_options_impl(config, substitutions, preset_name))

    config = _load_preset_files_impl(preset_file_names, substitutions)

    build_script_opts, missing_opts = \
        _get_opts(config, substitutions, preset_name)

    if not build_script_opts:
        diagnostics.fatal("preset '" + preset_name + "' not found")
    if missing_opts:
        diagnostics.fatal("missing option(s) for preset '" + preset_name
                          + "': " + ", ".join(missing_opts))

    return build_script_opts + ["--"]


def get_all_preset_names(preset_file_names):
    """
    Get a list of all presets in the preset files.

    preset_file_names -- list of the names of the preset files.
    """
    config = _load_preset_files_impl(preset_file_names)
    return [name[len(_PRESET_PREFIX):] for name in config.sections()
            if name.startswith(_PRESET_PREFIX)]


def parse_preset_substitutions(args):
    """
    Parse the preset substitutions from the parsed arguments and return them as
    a dictionary.

    args -- the parsed arguments of the program in preset mode.
    """

    # Create a list of tuples from the split raw argument substitutions.
    subs = [tuple(x.split("=", 1)) for x in args.preset_substitutions_raw]

    # 'dict()' creates automatically a dictionary from list of tuples.
    return dict(subs)
