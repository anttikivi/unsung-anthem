#===------------------------- http_stream.py -----------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module for streaming files.
"""


import platform
import sys

import requests

from script_support import data

from . import diagnostics, shell


def stream(url, destination, headers=None):
    """
    Stream a file to the local machine.

    url -- the url from which the file is streamed.
    destination -- the local file where the file is streamed.
    headers -- the possible headers for the HTTP call.
    """
    diagnostics.debug("Streaming an asset from {}".format(url))
    if data.build.ci or sys.version_info.major < 3:
        if platform.system() == "Windows":
            if headers:
                response = requests.get(url=url, headers=headers, stream=True)
            else:
                response = requests.get(url=url, stream=True)
            with open(destination, "wb") as destination_file:
                for chunk in response.iter_content(chunk_size=1024):
                    if chunk:
                        destination_file.write(chunk)
        else:
            shell.curl(url, destination)
        return
    if headers:
        response = requests.get(url=url, headers=headers, stream=True)
    else:
        response = requests.get(url=url, stream=True)
    with open(destination, "wb") as destination_file:
        for chunk in response.iter_content(chunk_size=1024):
            if chunk:
                destination_file.write(chunk)
    diagnostics.debug_ok(
        "Finished streaming an asset to {}".format(destination))
