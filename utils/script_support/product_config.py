#===-------------------------- product_config.py -------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the types for the product configurations of the
build.
"""


from build_utils.mapping import Mapping


def ode_anthem_config(version, name, key, **kwargs):
    """
    Create a mapping of the configuration of Obliging Ode or Unsung Anthem.
    """
    result = dict(**kwargs)
    result["version"] = version
    result["name"] = name
    result["key"] = key
    result["repr"] = "{} ({})".format(name, key)
    return Mapping(result)


def product_config(
        version, key, name, anthem_only=False, version_format=None,
        github_data=None, **kwargs):
    """Create a mapping of the configuration of a product."""
    result = dict(**kwargs)
    if isinstance(version, dict):
        if version.patch_minor == 0:
            version_string = "{}.{}.{}".format(
                version.major, version.minor, version.patch)
        else:
            version_string = "{}.{}.{}.{}".format(
                version.major, version.minor, version.patch,
                version.patch_minor)
        result["version"] = version_string
        result["version_mapping"] = version
    else:
        result["version"] = version
    result["version_format"] = version_format
    result["github_data"] = github_data
    result["name"] = name
    result["key"] = key
    result["anthem_only"] = anthem_only
    if name == key:
        result["repr"] = "{}".format(name)
    else:
        result["repr"] = "{} ({})".format(name, key)
    return Mapping(result)


def version_config(major, minor, patch, patch_minor=0):
    """Create a mapping representing the version of a product."""
    return Mapping(
        major=major, minor=minor, patch=patch, patch_minor=patch_minor)


def github_config(owner, name, asset_data, version_prefix=None):
    """Create a mapping of the GitHub configuration of a product."""
    result = Mapping(owner=owner, name=name, asset=asset_data)
    if version_prefix:
        result.version_prefix = version_prefix
    else:
        result.version_prefix = None
    return result


def asset(asset_file):
    """
    Create a simple mapping of the GitHub asset configuration of a product.
    """
    return Mapping(platform_specific=False, source=False, file=asset_file)


# A simple mapping of the GitHub asset source code configuration of a product.
SOURCE_ASSET = Mapping(
    platform_specific=False, source=True, fallback=False, fallback_file=None)


def platform_specific_asset(asset_file, platform_files, fallback_file=None):
    """
    Create a platform-specific mapping of the GitHub asset configuration of
    a product.
    """
    result = Mapping(
        platform_specific=True, source=False, file=asset_file,
        platform_files=platform_files)
    if fallback_file:
        result.fallback = True
        result.fallback_file = fallback_file
    else:
        result.fallback = False
        result.fallback_file = None
    return result


def platform_file_config(darwin=None, windows=None, linux=None):
    """
    Create a mapping of the platform-specific files of the asset configuration.
    """
    return Mapping(Darwin=darwin, Windows=windows, Linux=linux)
