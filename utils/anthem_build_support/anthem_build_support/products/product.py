# anthem_build_support/products/product.py -----------------------*- python -*-
#
# This source file is part of the Unsung Anthem open source project and is
# adapted from the Swift.org open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0
#
# ----------------------------------------------------------------------------

from .. import shell


class Product(object):
    @classmethod
    def product_name(cls):
        """
        product_name() -> str

        The identifier-style name to use for this product.
        """
        return cls.__name__.lower()

    @classmethod
    def product_source_name(cls):
        """
        product_source_name() -> str

        The name of the source code directory of this product.
        It provides a customization point for Product subclasses. It is set to
        the value of product_name() by default for this reason.
        """
        return cls.product_name()

    @classmethod
    def get_build_directory_name(cls, host_target):
        return '{}-{}'.format(cls.product_name(),
                              host_target.name)

    def __init__(self, args, toolchain, workspace, source_dir, build_dir):
        self.args = args
        self.toolchain = toolchain
        self.workspace = workspace
        self.source_dir = source_dir
        self.build_dir = build_dir
        self.cmake_options = []

    def bazel(self):
        # Copy the source tree to the build directory.
        shell.rmtree(self.build_dir)
        shell.copytree(self.source_dir, self.build_dir)
