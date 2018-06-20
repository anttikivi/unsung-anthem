#===----------------------------- checkout.py ----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0


"""The support module containing the utilities for checkouts."""


import os

from build_utils import shell, workspace


def clean_checkout(product):
    """
    Cleans up the old checkout and creates the directories necessary for the
    new one.
    """
    shell.rmtree(workspace.source_dir(product=product))
    shell.rmtree(workspace.temp_dir(product=product))
    shell.makedirs(workspace.source_dir(product=product))
    shell.makedirs(workspace.temp_dir(product=product))
