#===------------------------ product_config.py ---------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the types for the product configurations of the
build.
"""


from ..mapping import Mapping


def anthem_config(version):
    """
    Create a mapping of the configuration of Unsng Anthem.

    version -- the version of the product.
    """
    return Mapping(
        version=version,
        name="Unsung Anthem",
        identifier="anthem",
        repr="{name} ({identifier})".format(
            name="Unsung Anthem", identifier="anthem"))


def product_config(version, identifier, name, allow_git_checkout=False,
                   version_format=None, github_data=None, **kwargs):
    """
    Create a mapping of the configuration of a product.

    version -- the version of the product.
    identifier -- the identifier of the product.
    name -- the display name of the product.
    allow_git_checkout -- whether or not the product supports the version to be
    set to 'git'.
    version_format -- custom version format for the metavariable in the command
    line options.
    github_data -- the data with which the product is fetched. If the GitHub
    data are not provided, a function in module with the name of the dependency
    in the products is used to download the product.
    kwargs -- other key-value arguments to be added to the product mapping.
    """
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

    result["allow_git_checkout"] = allow_git_checkout
    result["version_format"] = version_format
    result["github_data"] = github_data
    result["name"] = name
    result["identifier"] = identifier
    if name == identifier:
        result["repr"] = "{name}".format(name=name)
    else:
        result["repr"] = "{name} ({identifier})".format(
            name=name, identifier=identifier)

    return Mapping(result)


def version_config(major, minor, patch, patch_minor=0):
    """
    Create a mapping representing the version of a product.

    major -- the major version number of the product.
    minor -- the minor version number of the product.
    patch -- the patch version number of the product.
    patch_minor -- the optional minor patch version number of the product.
    """
    return Mapping(
        major=major, minor=minor, patch=patch, patch_minor=patch_minor)


def github_config(owner, name, asset_data, version_prefix=None):
    """
    Create a mapping of the GitHub configuration of a product.

    owner -- the owner of the GitHub repository.
    name -- the name of the GitHub repository.
    asset_data -- the GitHub asset data.
    version_prefix -- a prefix which is used before the version.
    """
    result = Mapping(owner=owner, name=name, asset=asset_data)

    if version_prefix:
        result.version_prefix = version_prefix
    else:
        result.version_prefix = None

    return result


def asset(asset_file):
    """
    Create a simple mapping of the GitHub asset configuration of a product.

    asset_file -- the name of the asset file which is downloaded.
    """
    return Mapping(platform_specific=False, source=False, file=asset_file)


# A simple mapping of the GitHub asset source code configuration of a product.
SOURCE_ASSET = Mapping(
    platform_specific=False, source=True, fallback=False, fallback_file=None)


def platform_specific_asset(asset_file, platform_files, fallback_file=None):
    """
    Create a platform-specific mapping of the GitHub asset configuration of
    a product.

    asset_file -- the name of the asset file to which the file is downloaded.
    platform_file -- a mapping containing the names of the files for each
    platform.
    fallback_file -- the file which is downloaded if the platform-specific
    files are not available.
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

    darwin -- the name of the file on Darwin.
    windows -- the name of the file on Windows.
    linux -- the name of the file on Linux.
    """
    return Mapping(Darwin=darwin, Windows=windows, Linux=linux)
