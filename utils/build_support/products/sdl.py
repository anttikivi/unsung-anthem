#===---------------------------- sdl.py -----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the SDL product helpers.
"""


import os
import platform

import requests

from .. import diagnostics, shell

from ..httpstream import stream_file

from ..variables import ANTHEM_SOURCE_ROOT


def move_release_files(build_data):
    """
    """
    product = build_data.products.sdl
    version = product.version
    subdir = "SDL2-{}".format(version)
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", version))

    diagnostics.debug(
        "The name of the {} subdirectory is {}".format(product.repr, subdir))

    shell.copytree(
        os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp", subdir),
        os.path.join(ANTHEM_SOURCE_ROOT, "sdl", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))


def get_dependency(build_data):
    """
    """
    product = build_data.products.sdl
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))

    # TODO: protocol=build_data.connection_protocol
    if platform.system() == "Windows":
        archive_extension = "zip"
        url = product.windows_format.format(
            protocol="http", version=version, type="VC",
            extension=archive_extension
        )
    else:
        archive_extension = "tar.gz"
        url = product.url_format.format(
            protocol="http", version=version, extension=archive_extension
        )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "sdl", "temp", "sdl.{}".format(archive_extension)
    )

    stream_file(url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))
    shell.rm(destination)
    move_release_files(build_data=build_data)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))


def build(build_data):
    """
    """
