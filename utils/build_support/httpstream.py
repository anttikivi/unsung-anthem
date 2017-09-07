#===------------------------- httpstream.py -------------------*- python -*-===#
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


import requests

from . import diagnostics


def stream_file(url, destination):
    """
    """
    diagnostics.debug("Streaming an asset from {}".format(url))
    responce = requests.get(url=url, stream=True)
    with open(destination, "wb") as destination_file:
        for chunk in responce.iter_content(chunk_size=1024):
            if chunk:
                destination_file.write(chunk)
    diagnostics.debug_ok(
        "Finished streaming an asset to {}".format(destination))
