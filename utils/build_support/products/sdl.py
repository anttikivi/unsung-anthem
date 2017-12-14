#===---------------------------- sdl.py -----------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the GLFW product helpers.
"""


import os
import platform

from .product import binary_exists, build_call, check_source

from .. import diagnostics, shell, workspace

from ..httpstream import stream_file

from ..variables import ANTHEM_SOURCE_ROOT


def move_release_files(build_data):
    """
    Move the SDL files to the correct location after the download.
    build_data -- the build data.
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
    Download SDL.
    build_data -- the build data.
    """
    product = build_data.products.sdl
    version = product.version
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", version))
    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", version))
    shell.makedirs(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))

    if platform.system() == "Windows":
        archive_extension = "zip"
        url = product.windows_format.format(
            protocol=build_data.connection_protocol, version=version,
            type="VC", extension=archive_extension
        )
    else:
        archive_extension = "tar.gz"
        url = product.url_format.format(
            protocol="http", version=version, extension=archive_extension
        )
    destination = os.path.join(
        ANTHEM_SOURCE_ROOT, "sdl", "temp", "sdl.{}".format(archive_extension)
    )

    stream_file(build_data=build_data, url=url, destination=destination)

    shell.tar(
        path=destination,
        dest=os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))
    shell.rm(destination)
    move_release_files(build_data=build_data)

    shell.rmtree(os.path.join(ANTHEM_SOURCE_ROOT, "sdl", "temp"))


def do_build_windows(build_data):
    """
    Do the build of SDL on Windows.
    build_data -- the build data.
    """
    product = build_data.products.sdl
    bin_path = workspace.lib_file(build_data=build_data, path="SDL2.lib")
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    source_dir = workspace.source_dir(product=product)
    shell.rmtree(build_dir)
    shell.copytree(source_dir, build_dir)
    include_dir = workspace.include_file(build_data=build_data, path="SDL2")
    if not workspace.is_include_dir_made(build_data=build_data) \
            and workspace.include_file_exists(
                build_data=build_data, path="SDL2"):
        shell.rmtree(include_dir)
    shell.copytree(os.path.join(build_dir, "include"), include_dir)
    if not workspace.is_lib_dir_made(build_data):
        for lib_file in os.listdir(
                os.path.join(build_data.install_root, "lib")):
            if "SDL" in lib_file:
                shell.rm(workspace.lib_file(
                    build_data=build_data, path=lib_file
                ))
    for lib_file in os.listdir(os.path.join(build_dir, "lib", "x86")):
        shell.copy(
            os.path.join(build_dir, "lib", "x86", lib_file),
            workspace.lib_file(build_data=build_data, path=lib_file)
        )


def do_build(build_data):
    """
    Do the build of SDL.
    build_data -- the build data.
    """
    product = build_data.products.sdl
    bin_path = os.path.join(build_data.install_root, "lib", "libSDL2.a")
    build_dir = workspace.build_dir(build_data=build_data, product=product)
    if binary_exists(build_data=build_data, product=product, path=bin_path):
        return
    shell.makedirs(build_dir)
    build_call(build_data=build_data, product=product)


def build(build_data):
    """
    Build SDL.
    build_data -- the build data.
    """
    product = build_data.products.sdl
    check_source(product=product)
    if platform.system() == "Windows":
        do_build_windows(build_data=build_data)
    else:
        do_build(build_data=build_data)


def copy_dynamic(build_data, dest):
    """
    Move the dynamic library on Windows.
    build_data -- the build data.
    dest -- the directory to which the library is copied.
    """
    bin_path = workspace.lib_file(build_data=build_data, path="SDL2.dll")
    dest_path = os.path.join(dest, "SDL2.dll")
    if os.path.exists(dest_path):
        return
    shell.copy(bin_path, dest)
