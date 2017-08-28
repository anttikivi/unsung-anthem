#===------------------------ product_config.py ----------------*- python -*-===#
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


from .. import mapping


def product_config(version, github_data=None):
    """
    Create a mapping of the configuration of a product.

    version -- the version of the product.
    github_data -- the data with which the product is fetched. If the GitHub
    data are not provided, a function in module wiht the name of the dependency
    in the products is used.
    """

    if isinstance(version, mapping.Mapping):
        version_string = \
            "{}.{}.{}".format(version.major, version.minor, version.patch) \
            if version.patch_minor == 0 else \
            "{}.{}.{}.{}".format(
                version.major, version.minor, version.patch,
                version.patch_minor)
        result = mapping.Mapping(
            version=version_string, version_mapping=version)
    else:
        result = mapping.Mapping(version=version)

    if github_data:
        result.github_data = github_data

    return result


def version_config(major, minor, patch, patch_minor=0):
    """
    """

    return mapping.Mapping(major=major, minor=minor, patch=patch,
                           patch_minor=patch_minor)


def github_config(owner, name, asset_data, version_prefix=None):
    """
    Create a mapping of the GitHub configuration of a product.

    owner -- the owner of the GitHub repository.
    name -- the name of the GitHub repository.
    asset_data -- the GitHub asset data.
    version_prefix -- a prefix which is used before the version.
    """

    result = mapping.Mapping(owner=owner, name=name, asset=asset_data)

    if version_prefix:
        result.version_prefix = version_prefix

    return result


def asset(asset_file):
    """
    Create a simple mapping of the GitHub asset configuration of a product.

    asset_file -- the name of the asset file which is downloaded.
    """

    return mapping.Mapping(platform_specific=False, source=False,
                           file=asset_file)


# A simple mapping of the GitHub asset source code configuration of a product.
SOURCE_ASSET = mapping.Mapping(platform_specific=False, source=True)


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

    result = mapping.Mapping(platform_specific=True, source=False,
                             file=asset_file, platform_files=platform_files)

    if fallback_file:
        result.fallback = True
        result.fallback_file = fallback_file

    return result


def platform_file_config(darwin=None, windows=None, linux=None):
    """
    Create a mapping of the platform-specific files of the asset configuration.

    darwin -- the name of the file on Darwin.
    windows -- the name of the file on Windows.
    linux -- the name of the file on Linux.
    """

    return mapping.Mapping(Darwin=darwin, Windows=windows, Linux=linux)
