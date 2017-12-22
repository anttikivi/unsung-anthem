#===---------------------- driver_arguments.py ---------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the script options.
"""


from build_support import targets
from build_support.targets import host_target

from . import argparse
from . import defaults


__all__ = [
    "create_argument_parser",
]


class _ApplyDefaultsArgumentParser(argparse.ArgumentParser):
    """
    Wrapper class around the default ArgumentParser that allows for
    post-processing the parsed argument namespace to apply default argument
    transformations.
    """

    def __init__(self, apply_defaults=None, *args, **kwargs):
        self._apply_defaults = apply_defaults
        super(_ApplyDefaultsArgumentParser, self).__init__(*args, **kwargs)

    def parse_known_args(self, args=None, namespace=None):
        args, argv = super(_ApplyDefaultsArgumentParser, self)\
            .parse_known_args(args, namespace)

        self._apply_defaults(args)
        return args, argv


def _apply_default_arguments(args):
    """
    Preprocess argument namespace to apply default behaviors.
    """


def create_argument_parser():
    """Return a configured argument parser."""

    # NOTE: USAGE, DESCRIPTION and EPILOG are defined at the bottom of the file
    parser = _ApplyDefaultsArgumentParser(
        apply_defaults=_apply_default_arguments,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        usage=USAGE,
        description=DESCRIPTION,
        epilog=EPILOGUE)

    builder = parser.to_builder()

    # Prepare DSL functions
    option = builder.add_option
    set_defaults = builder.set_defaults
    in_group = builder.in_group
    mutually_exclusive_group = builder.mutually_exclusive_group

    # Prepare DSL actions
    append = builder.actions.append
    store = builder.actions.store
    store_true = builder.actions.store_true
    store_false = builder.actions.store_false
    store_int = builder.actions.store_int
    store_path = builder.actions.store_path
    toggle_true = builder.actions.toggle_true
    toggle_false = builder.actions.toggle_false
    unsupported = builder.actions.unsupported

    # -------------------------------------------------------------------------
    # Top-level options

    option(
        ["-n", "--dry-run"],
        store_true,
        help="print the commands that would be executed, but don't execute "
             "them")
    option(
        "--from-preset",
        store_true,
        help="the build is run as if it was called by the preset mode. You "
             "mustn't set this yourself")

    option(
        "--build-subdir",
        store,
        metavar="PATH",
        help="name of the directory under $ANTHEM_BUILD_ROOT where the build "
             "products will be placed")
    option(
        "--install-prefix",
        store_path,
        # TODO: default=targets.install_prefix(),
        help="The installation prefix. This is where built Unsung Anthem "
             "products (like bin, lib, and include) will be installed.")

    option(
        "--cmake",
        store_path(executable=True),
        help="the path to a CMake executable that will be used to build "
             "Unsung Anthem")

    option(
        "--host-cc",
        store_path(executable=True),
        help="the absolute path to CC, the C compiler for the host platform. "
             "Default is auto detected")
    option(
        "--host-cxx",
        store_path(executable=True),
        help="the absolute path to CXX, the C++ compiler for the host "
             "platform. Default is auto detected")

    option(
        "--anthem-version",
        store,
        default=defaults.ANTHEM_VERSION,
        metavar="MAJOR.MINOR.PATCH",
        help="the version of Unsung Anthem")

    option(
        "--darwin-deployment-version",
        store,
        default=defaults.DARWIN_DEPLOYMENT_VERSION,
        metavar="MAJOR.MINOR",
        help="minimum deployment target version for macOS")

    option(
        "--cmake-extra-options",
        append,
        type=argparse.ShellSplitType(),
        help="pass through extra options to CMake in the form of comma "
             "separated options '-DCMAKE_VAR1=YES,-DCMAKE_VAR2=/tmp'. Can be "
             "called multiple times to add multiple such options")

    option(
        ["-v", "--verbose-build"],
        toggle_true,
        help="print the commands executed during the build")

    return builder.build()


# ----------------------------------------------------------------------------

# The usage of the program which is printed when the full program help option
# is used or the program is called with invalid arguments.
USAGE = """
  %(prog)s [-h | --help] [OPTION...]
  %(prog)s --preset=NAME [SUBSTITUTION...]
"""


# The description which is printed when the full program help option is used.
DESCRIPTION = """
Use this tool to build, test, and prepare binary distribution archives of
Unsung Anthem.

Builds Unsung Anthem and its dependencies, incrementally, optionally testing
Unsung Anthem thereafter. Different build configurations are maintained in
parallel."""


# The epilogue which is printed when the full program help option is used.
EPILOGUE = """
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
