#===------------------------------- which.py -----------------*- python -*-===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the 'which' helper.
"""


from __future__ import absolute_import

import sys

from . import cache_util, shell


@cache_util.cached
def which(cmd):
    """
    Return the path to an executable which would be run if the given cmd was
    called. If no cmd would be called, return None.

    Python 3.3+ provides this behaviour via the shutil.which() function;
    see: https://docs.python.org/3.3/library/shutil.html#shutil.which

    We provide our own implementation because shutil.which() has not
    been backported to Python 2.7, which we support.

    cmd -- the command which is looked for.
    """
    if sys.version_info[0] >= 3:
        import shutil
        return shutil.which(cmd)
    out = shell.capture(
        ["which", cmd], dry_run=False, echo=False, optional=True)
    if out is None:
        return None
    return out.rstrip()


@cache_util.cached
def where(cmd):
    """
    Return the path to an executable which would be run if the given cmd was
    called. If no cmd would be called, return None.

    Python 3.3+ provides this behaviour via the shutil.which() function;
    see: https://docs.python.org/3.3/library/shutil.html#shutil.which

    We provide our own implementation because shutil.which() has not
    been backported to Python 2.7, which we support.

    cmd -- the command which is looked for.
    """
    if sys.version_info[0] >= 3:
        import shutil
        return shutil.which(cmd)
    out = shell.capture(
        ["where.exe", cmd], dry_run=False, echo=False, optional=True)
    if out is None:
        return None
    return out.rstrip()
