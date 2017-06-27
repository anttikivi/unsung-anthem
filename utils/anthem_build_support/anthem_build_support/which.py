# anthem_build_support/which.py - shutil.which() for Python 2.7 -*- python --*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------
#
# A naive reimplementation of shutil.which() for Python 2.7. This can be
# removed if shutil.which() is backported, or if the Unsung Anthem build
# toolchain migrates completely to Python 3.3+.
#
# ----------------------------------------------------------------------------

from __future__ import absolute_import

from . import cache_util
from . import shell


@cache_util.cached
def which(cmd):
    """
    Return the path to an executable which would be run if
    the given cmd was called. If no cmd would be called, return None.

    Python 3.3+ provides this behavior via the shutil.which() function;
    see: https://docs.python.org/3.3/library/shutil.html#shutil.which

    We provide our own implementation because shutil.which() has not
    been backported to Python 2.7, which we support.
    """
    out = shell.capture(['which', cmd],
                        dry_run=False,
                        echo=False,
                        optional=True)
    if out is None:
        return None
    return out.rstrip()
