#===---------------------- driver_arguments.py ---------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module containing the script options.
"""


from build_utils import diagnostics

from build_utils.targets import host_target

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
        args, argv \
            = super(_ApplyDefaultsArgumentParser, self).parse_known_args(
                args,
                namespace)

        self._apply_defaults(args)
        return args, argv


def _apply_default_arguments(args):
    """
    Preprocess argument namespace to apply default behaviours.
    """
    diagnostics.trace("Applying default arguments")

    if args.std is None:
        args.std = "c++14"

    # Set the default CMake generator.
    if args.cmake_generator is None:
        args.cmake_generator = "Ninja"


def create_argument_parser():
    """Return a configured argument parser."""

    diagnostics.trace("Creating argument parser builder")

    # NOTE: USAGE, DESCRIPTION and EPILOGUE are defined at the bottom of
    # the file
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

    diagnostics.trace("Creating command line arguments")

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
        "--darwin-xcrun-toolchain",
        store,
        default=defaults.DARWIN_XCRUN_TOOLCHAIN,
        help="the name of the toolchain to use on Darwin")
    option(
        "--cmake",
        store_path(executable=True),
        help="the path to a CMake executable that will be used to build "
             "Unsung Anthem")
    option(
        "--git",
        store_path(executable=True),
        help="the path to a git executable that will be used in the build of "
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
        "--main-tool",
        store,
        default="llvm",
        help="the name of the main tool to be looked by the script. The "
             "default is llvm")
    option(
        "--main-tool-version",
        store,
        default="default",
        help="the version of the main tool which will be used in the lookup "
             "of the tool")

    # TODO
    option(
        ["-v", "--verbose-build"],
        toggle_true,
        help="print the commands executed during the build")

    # -------------------------------------------------------------------------
    in_group("TODO: Host and cross-compilation targets")

    option(
        "--host-target",
        store,
        default=host_target().name,
        help="the host target. Unsung Anthem will be built for this target")
    option(
        "--cross-compile-hosts",
        append,
        type=argparse.ShellSplitType(),
        default=[],
        help="a space separated list of targets to cross-compile Unsung "
             "Anthem for. Can be used multiple times")

    # -------------------------------------------------------------------------
    in_group("Options to select projects")

    option(
        "--llvm",
        toggle_true("build_llvm"),
        help="build LLVM and use the built LLVM")
    option(
        "--source-llvm",
        toggle_true,
        help="build LLVM from the source instead of downloading the pre-built "
             "binaries. Implies '--llvm'")
    option(
        "--libc++",
        toggle_true("build_libcxx"),
        help="build libc++ and use the built library to build the project")
    # TODO: Should this be removed and the ninja be built if the script sees it
    # necessary?
    option("--build-ninja", toggle_true, help="build the Ninja tool")

    # -------------------------------------------------------------------------
    in_group("Select the C++ standard")

    with mutually_exclusive_group():
        set_defaults(std="c++14")

        option("--c++14",
               store("std"),
               const="c++14",
               help="build using the C++14 standard (default is %(default)s)")
        option("--c++17",
               store("std"),
               const="c++17",
               help="build using the C++17 standard (default is %(default)s)")
        option("--c++2a",
               store("std"),
               const="c++2a",
               help="build using the next C++ standard (default is "
                    "%(default)s)")

    # -------------------------------------------------------------------------
    in_group("Select the C++ standard library")

    option(
        "--stdlib",
        store,
        default="libc++",
        help="build using the specified C++ standard library implementation")

    # -------------------------------------------------------------------------
    in_group("Select the CMake generator")

    set_defaults(cmake_generator=defaults.CMAKE_GENERATOR)

    option(
        ["-e", "--eclipse"],
        store("cmake_generator"),
        const="Eclipse CDT4 - Ninja",
        help="use CMake's Eclipse generator (%(default)s by default)")
    option(
        ["-m", "--make"],
        store("cmake_generator"),
        const="Unix Makefiles",
        help="use CMake's Makefile generator (%(default)s by default)")
    option(
        ["-x", "--xcode"],
        store("cmake_generator"),
        const="Xcode",
        help="use CMake's Xcode generator (%(default)s by default)")

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
