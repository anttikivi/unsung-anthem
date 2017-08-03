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


def _load_preset_files_impl(preset_file_names, defaults=None):
    """
    Load the presets in the preset files.

    preset_file_names -- the names of the files from which the presets are loaded.
    defaults -- key-value pair to be default values in the presets.
    """

    if defaults is None:
        defs = {}
    else:
        defs = defaults

    config = ConfigParser.SafeConfigParser(defs, allow_no_value=True)
    if not config.read(preset_file_names):
        diagnostics.fatal("preset file not found (tried "
                          + str(preset_file_names)
                          + ")")
    diagnostics.debug("loaded preset config from " + str(preset_file_names))
    return config


_PRESET_PREFIX = "preset: "


def _impl_get_preset_options(config, defaults, preset_name):
    """
    Concatenate the lists of options in the preset.

    config -- the preset file information.
    defaults -- the preset default values.
    preset_name -- the name of the preset.
    parser -- the function used to parse the options.
    """

    def _get_value(option):
        # A dirty try-catch.
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
        def _impl(option):
            value = _get_value(option)

            if not option == "mixin-preset":
                if value == "":
                    diagnostics.debug("'" + option + "' in preset '"
                                      + preset_name + "' is set (to true)")
                else:
                    diagnostics.debug("'" + option + "' in preset '"
                                      + preset_name + "' is set to '" + value
                                      + "'")
            else:
                diagnostics.debug("skipping the mix-in preset option in this "
                                  "phase")

            if option in defaults:
                diagnostics.debug(option + " was found from default values")
                return None

            if option == "mixin-preset":
                # Mixins are handled separately.
                return None
            elif value == "":
                return "--" + option

            return "--" + option + "=" + value

        return _impl(option)

    def parse_mixins():
        """
        Parse mix-in presets of the preset and return the parsed options from
        the mix-in presets.
        """
        def _impl():
            value = _get_value("mixin-preset")

            if "mixin-preset" in defaults:
                return None

            # Split on newlines and filter out empty lines.
            mixins = filter(None, [m.strip() for m in value.splitlines()])
            diagnostics.debug("found the following mix-in presets: "
                              + str(mixins))
            mixin_opts = [_impl_get_preset_options(config, defaults, m)
                          for m in mixins]

            ret = list(itertools.chain.from_iterable(mixin_opts))

            diagnostics.debug("mix-in preset(s) of '" + preset_name
                              + "' (which are " + str(mixins) + ") yield(s): "
                              + ", ".join(ret))

            return ret

        return _impl()

    diagnostics.debug("now parsing " + preset_name)

    section_name = _PRESET_PREFIX + preset_name

    if section_name not in config.sections():
        return None

    build_script_opts = filter(None, [parse_option(opt)
                                      for opt in config.options(section_name)])

    diagnostics.debug_ok("build script options of '" + preset_name + "' are: "
                         + ", ".join(build_script_opts))

    mixin_opts = filter(None, [(opt if opt == "mixin-preset" else None)
                               for opt in config.options(section_name)])

    if mixin_opts:
        diagnostics.debug("mix-in preset(s) found in '" + preset_name + "'")
        mixins = filter(None, parse_mixins())
    else:
        diagnostics.debug("no mix-in presets found in '" + preset_name + "'")
        mixins = []

    ret = list(build_script_opts + mixins)

    diagnostics.debug_ok("option(s) of '" + preset_name + "' are: "
                         + ", ".join(ret))

    return ret


def get_preset_options(defaults, preset_file_names, preset_name):
    """
    Get a list of the options in the preset.

    defaults -- the preset default values.
    preset_file_names -- list of the names of the preset files.
    preset_name -- the name of the preset.
    """
    diagnostics.debug("starting to get options from the preset " + preset_name)

    config = _load_preset_files_impl(preset_file_names, defaults)

    build_script_opts = \
        _impl_get_preset_options(config, defaults, preset_name)

    if not build_script_opts:
        diagnostics.fatal("preset '" + preset_name + "' not found")

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

    # Create a list of tuples from the split raw argument defaults.
    defaults = [tuple(x.split("=", 1)) for x in args.preset_defaults_raw]

    diagnostics.debug("preset default values are " + str(dict(defaults)))

    # 'dict()' creates automatically a dictionary from list of tuples.
    return dict(defaults)
