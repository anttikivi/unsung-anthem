# ------------------------------------------------------------- #
#                 Obliging Ode & Unsung Anthem
# ------------------------------------------------------------- #
#
# This source file is part of the Obliging Ode and Unsung Anthem
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved
#
# ------------------------------------------------------------- #


"""This tool runs Couplet Composer."""


from __future__ import print_function

import os
import platform
import shutil
import subprocess
import sys


USE_DEVELOP_STACK = any([(opt == "-S" or opt == "--develop-stack")
                        for opt in sys.argv[1:]])
DRY_RUN = any([(opt == "-n" or opt == "--dry-run") for opt in sys.argv[1:]])


ODE_DEFAULT_BUILD_VERSION = "0.3.0"
ODE_BUILD_KEY = "couplet-composer"
REPO_OWNER = "anttikivi"
REPO_NAME = ODE_BUILD_KEY
BUILD_LOCATION = os.path.join("build")
# The name of the directory where the script is stored for build
SCRIPT_DIR_NAME = "script"
# The location where the script is stored when using the
# development version
SCRIPT_LOCATION = os.path.join(BUILD_LOCATION, SCRIPT_DIR_NAME)
GRAPHQL_LOCATION = os.path.join(BUILD_LOCATION, "graphql")


def caffeinate(command):
    """
    Run a command during which system sleep is disabled. This
    ignores the 'shell.dry_run' flag.
    """
    # Disable system sleep, if possible.
    if platform.system() == "Darwin":
        # Don't change the caller's copy of the arguments.
        command = ["caffeinate"] + list(command)
    try:
        subprocess.check_call(command)
    except subprocess.CalledProcessError as e:
        SystemExit(
            "Command ended with a non-zero exit status "
            "{}".format(e.returncode))
    except OSError as e:
        SystemExit("Could not run the build script: {}".format(e.strerror))


def _build_script_dev(dir_name):
    """Build Couplet Composer."""
    # destination = os.path.join(BUILD_LOCATION, SCRIPT_DIR_NAME)
    # args = [
    #     sys.executable,
    #     os.path.join(destination, "setup.py"),
    #     "install"
    # ]
    # print("Running the build of the composer: {}".format(args))
    # caffeinate(args)
    # if os.path.isdir(SCRIPT_LOCATION):
    #     shutil.rmtree(SCRIPT_LOCATION)
    # os.makedirs(SCRIPT_LOCATION)
    # src_dir = os.path.join(BUILD_SCRIPT_LOCATION, "build", "lib")
    # for item in os.listdir(src_dir):
    #     src = os.path.join(src_dir, item)
    #     dest = os.path.join(SCRIPT_LOCATION, item)
    #     if os.path.isdir(src):
    #         shutil.copytree(src, dest)
    #     else:
    #         shutil.copy2(src, dest)
    # shutil.copy2(
    #     os.path.join(BUILD_SCRIPT_LOCATION, "run.py"),
    #     os.path.join(SCRIPT_LOCATION, "run.py"))


def _copy_script_dev():
    """Copy Couplet Composer to the build directory."""
    destination = os.path.join(BUILD_LOCATION, SCRIPT_DIR_NAME)
    if not os.path.isdir(BUILD_LOCATION):
        print("The directory " + BUILD_LOCATION + " doesn't exist")
        os.makedirs(BUILD_LOCATION)
    else:
        if os.path.isdir(destination):
            shutil.rmtree(destination)
    os.makedirs(destination)

    def _copy_script_dir(name):
        src_dir = os.path.join(REPO_NAME, name)
        dest_dir = os.path.join(destination, name)
        os.makedirs(dest_dir)
        for item in os.listdir(src_dir):
            src = os.path.join(src_dir, item)
            dest = os.path.join(dest_dir, item)
            if os.path.isdir(src):
                shutil.copytree(src, dest)
            else:
                shutil.copy2(src, dest)
    _copy_script_dir("components")
    _copy_script_dir("github")
    _copy_script_dir("graphql")
    _copy_script_dir(REPO_NAME.replace("-", "_").lower())
    _copy_script_dir("support")
    _copy_script_dir("util")

    def _copy_script_file(name):
        src_file = os.path.join(REPO_NAME, name)
        dest_file = os.path.join(destination, name)
        shutil.copy2(src_file, dest_file)
    _copy_script_file("run.py")
    _copy_script_file("LICENCE")
    _copy_script_file("MANIFEST.in")
    _copy_script_file("README.md")
    _copy_script_file("setup.py")


def _copy_graphql():
    if os.path.isdir(GRAPHQL_LOCATION):
        shutil.rmtree(GRAPHQL_LOCATION)
    os.makedirs(GRAPHQL_LOCATION)
    src_dir = os.path.join(SCRIPT_LOCATION, "graphql")
    for item in os.listdir(src_dir):
        src = os.path.join(src_dir, item)
        dest = os.path.join(GRAPHQL_LOCATION, item)
        if os.path.isdir(src):
            shutil.copytree(src, dest)
        else:
            shutil.copy2(src, dest)


def _run_dev(bootstrap):
    _copy_script_dev()
    if bootstrap:
        # _build_script_dev()
        _copy_graphql()
    args = [sys.executable]
    args += [os.path.join(SCRIPT_LOCATION, "run.py")]
    args += ["bootstrap" if bootstrap else "build"]
    args += sys.argv[1:]
    return caffeinate(args)


def bootstrap():
    if USE_DEVELOP_STACK:
        print(
            "Couplet Composer and related project won't be downloaded as you "
            "chose the development stack")
        return _run_dev(True)
    else:
        # _checkout(_download_v4)
        return 0  # _run()


def build():
    if USE_DEVELOP_STACK:
        print(
            "Couplet Composer and related project won't be downloaded as you "
            "chose the development stack")
        return _run_dev(False)
    else:
        # _checkout(_download_v4)
        return 0  # _run()
