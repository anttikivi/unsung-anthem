#===------------------------- httpstream.py ------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing helpers for streaming via HTTP.
"""


import sys

import requests

from . import diagnostics, shell


def stream_file(build_data, url, destination, headers=None):
    """
    Stream a file to the local machine.

    build_data -- the build data.
    url -- the url from which the file is streamed.
    destination -- the local file where the file is streamed.
    headers -- the possible headers for the HTTP call.
    """
    diagnostics.debug("Streaming an asset from {}".format(url))
    if build_data.args.ci or sys.version_info.major < 3:
        # TODO: Windows
        shell.curl(url, destination)
        return
    if headers:
        responce = requests.get(url=url, headers=headers, stream=True)
    else:
        responce = requests.get(url=url, stream=True)
    with open(destination, "wb") as destination_file:
        for chunk in responce.iter_content(chunk_size=1024):
            if chunk:
                destination_file.write(chunk)
    diagnostics.debug_ok(
        "Finished streaming an asset to {}".format(destination))
