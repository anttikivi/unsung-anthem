#===--------------------------- script.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing script-related helpers.
"""


import argparse
import os
import platform
import sys

from . import script_options

from .variables import HOME, ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME


# The usage of the program which is printed when the full program help option
# is used or the program is called with invalid arguments.
PROGRAM_USAGE = """
  %(prog)s [-h | --help] [OPTION...]
  %(prog)s --preset=NAME [SUBSTITUTION...]
"""


# The description which is printed when the full program help option is used.
PROGRAM_DESCRIPTION = """
Use this tool to build, test, and prepare binary distribution archives of
Unsung Anthem.

Builds Unsung Anthem and its dependencies, incrementally, optionally testing
Unsung Anthem thereafter. Different build configurations are maintained in
parallel."""


# The epilogue which is printed when the full program help option is used.
PROGRAM_EPILOGUE = """
Using option presets:

  --preset-file=PATH    load presets from the specified file

  --preset=NAME         use the specified option preset

  The preset mode is mutually exclusive with other options. It is not possible
  to add ad-hoc customizations to a preset. This is a deliberate design
  decision. (Rationale: a preset is a certain important set of options that is
  wanted to be kept in a centralized location. If one needs to customize it,
  one should create another preset in a centralized location, rather than
  scattering the knowledge about the build across the system.)

  Presets support substitutions for controlled customizations. Substitutions
  are defined in the preset file. Values for substitutions are supplied using
  the name=value syntax on the command line.


Environment variables
---------------------

This script respects a few environment variables, should one choose to set
them:

ANTHEM_SOURCE_ROOT: a directory containing the source for Unsung Anthem. If
                    this script is located in an Unsung Anthem source
                    directory, the location of ANTHEM_SOURCE_ROOT will be
                    inferred if the variable is not set.

'build-script' expects the sources to be laid out in the following way:

   $ANTHEM_SOURCE_ROOT/unsung-anthem (the directory name does not matter)

ANTHEM_BUILD_ROOT: a directory in which to create out-of-tree builds.
                   Defaults to "$ANTHEM_SOURCE_ROOT/build/".

Preparing to run this script
----------------------------

Make sure that your system has C and C++ compilers.

That's it; you're ready to go!

Examples
--------

Given the above layout of sources, the simplest invocation of 'build-script'
is just:

  [~/src/s]$ ./unsung-anthem/utils/build-script

This builds Unsung Anthem, its dependencies and the tools required to build it
in debug mode.

All builds are incremental. To incrementally build changed files, repeat the
same 'build-script' command.

Typical uses of 'build-script'
------------------------------

To build everything with optimization without debug information:

  [~/src/s]$ ./unsung-anthem/utils/build-script -R

To run tests, add '-t':

  [~/src/s]$ ./unsung-anthem/utils/build-script -R -t

To build dependencies and tools with optimization without debug information,
and a debuggable Unsung Anthem:

  [~/src/s]$ ./unsung-anthem/utils/build-script -R --debug-anthem

To use 'make' instead of 'ninja', use '-m':

  [~/src/s]$ ./unsung-anthem/utils/build-script -m -R

To create Xcode projects that can build Unsung Anthem, use '-x':

  [~/src/s]$ ./unsung-anthem/utils/build-script -x -R

Preset mode in build-script
---------------------------

All buildbots and automated environments use 'build-script' in *preset mode*.
In preset mode, the command line only specifies the preset name and allows
limited customization (extra output paths). The actual options come from the
selected preset in 'utils/build-presets.ini'.

If you have your own favourite set of options, you can create your own, local,
preset. For example, let's create a preset called 'dua' (which stands for Debug
Unsung Anthem):

  $ cat > ~/.anthem-build-presets
  [preset: dua]
  release
  debug-anthem
  test
  build-subdir=dua

To use it, specify the '--preset=' argument:

  [~/src/s]$ ./unsung-anthem/utils/build-script --preset=dua
  ./unsung-anthem/utils/build-script: using preset 'dua', which expands to
  ./unsung-anthem/utils/build-script --release --debug-anthem --test \
--build-subdir=dua --
  ...

Philosophy
----------

While one can invoke CMake directly to build Unsung Anthem, this tool will
save one's time by taking away the mechanical parts of the process, providing
one the controls for the important options.

For all automated build environments, this tool is regarded as *the* *only*
way to build Unsung Anthem. This is not a technical limitation of the Unsung
Anthem build system. It is a policy decision aimed at making the builds
uniform across all environments and easily reproducible by engineers who are
not familiar with the details of the setups of other systems or automated
environments.
"""


def create_preset_parser():
    """
    Create the argument parser to be used when the program is run in the
    preset mode.

    This function returns an object of type ArgumentParser.
    """
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        description="Builds Unsung Anthem using a preset.")

    parser.add_argument(
        "-n", "--dry-run",
        help="print the commands that would be executed, but don't execute "
             "them",
        action="store_true",
        default=False)
    parser.add_argument(
        "-c", "--clean",
        help="do a clean build",
        action="store_true")
    parser.add_argument(
        "--preset-file",
        help="load presets from the specified file",
        metavar="PATH",
        action="append",
        dest="preset_file_names",
        default=[])
    parser.add_argument(
        "--preset",
        help="use the specified option preset",
        metavar="NAME",
        required=True)
    parser.add_argument(
        "--show-presets",
        help="list all presets and exit",
        action="store_true")

    build_actions_group = parser.add_mutually_exclusive_group(required=False)
    build_actions_group.add_argument(
        "--install",
        help="only install the project dependencies",
        action="store_true",
        dest="install_only")
    build_actions_group.add_argument(
        "--build",
        help="build the project without installing the dependencies",
        action="store_true",
        dest="build_only")
    build_actions_group.add_argument(
        "--run-test",
        help="run the tests without installing the dependencies or building "
             "the project",
        action="store_true",
        dest="test_only")
    build_actions_group.add_argument(
        "--docs-only",
        help="build only the documentation",
        action="store_true",
        dest="docs_only")

    parser.add_argument(
        "-j", "--jobs",
        help="the number of parallel build jobs to use",
        type=int,
        dest="build_jobs")
    parser.add_argument(
        "preset_defaults_raw",
        help="'name=value' pairs that are default values in the preset",
        nargs="*",
        metavar="DEFAULTS")
    parser.add_argument(
        "--expand-build-script-invocation",
        help="Print the expanded build-script invocation generated "
             "by the preset, but do not run the preset",
        action="store_true")

    return parser


def create_parser():
    """
    Create the argument parser to be used when the program is run in the
    preset mode.

    This function is not pure, as it modifies the parser object before
    returning it.

    This function returns an object of type ArgumentParser.
    """
    parser = argparse.ArgumentParser(
        formatter_class=argparse.RawDescriptionHelpFormatter,
        usage=PROGRAM_USAGE,
        description=PROGRAM_DESCRIPTION,
        epilog=PROGRAM_EPILOGUE)

    parser = script_options.script_options(parser)
    parser = script_options.ci_options(parser)
    parser = script_options.target_options(parser)
    parser = script_options.projects_options(parser)
    parser = script_options.build_action_options(parser)
    parser = script_options.extra_action_options(parser)
    parser = script_options.cxx_options(parser)
    parser = script_options.build_variant_options(parser)
    parser = script_options.assertion_options(parser)
    parser = script_options.cmake_options(parser)
    parser = script_options.test_options(parser)
    parser = script_options.build_options(parser)
    parser = script_options.checkout_options(parser)
    parser = script_options.version_options(parser)
    parser = script_options.system_options(parser)
    parser = script_options.msbuild_options(parser)
    parser = script_options.program_options(parser)
    parser = script_options.authentication_options(parser)
    parser = script_options.miscellaneous_options(parser)

    return parser


def preset_files(args):
    """
    Get the files from which the program looks the presets up.

    args -- the parsed arguments of the program in preset mode.
    """

    if not args.preset_file_names:
        ret = [
            os.path.join(HOME, ".anthem-build-presets"),
            os.path.join(
                ANTHEM_SOURCE_ROOT, ANTHEM_REPO_NAME, "utils",
                "build-presets.ini"
            )
        ]
    else:
        ret = args.preset_file_names
    return ret


def get_new_invocation(args, preset_args):
    """
    Create the call for the actual build script invocation from the presets.

    args -- the command line arguments.
    preset_args -- the parsed preset arguments.
    """
    def _impl_exec():
        return [(sys.executable
                 if platform.system() == "Windows" else None), sys.argv[0]]

    return list(filter(None, list(
        _impl_exec() + [
            ("--from-preset"),
            ("--dry-run" if args.dry_run else None),
            ("--clean" if args.clean else None),
            ("--install" if args.install_only else None),
            ("--build" if args.build_only else None),
            ("--run-test" if args.test_only else None),
            ("--docs-only" if args.docs_only else None)
        ]
        + preset_args
        + [
            ("--jobs" if args.build_jobs else None),
            (str(args.build_jobs) if args.build_jobs else None)
        ])))
