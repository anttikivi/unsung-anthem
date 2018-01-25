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


import multiprocessing
import os

from build_utils.targets import host_target

from . import argparse
from . import defaults

from .variables import ANTHEM_REPO_NAME, ANTHEM_SOURCE_ROOT


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
    # Set the default build variant.
    if args.build_variant is None:
        args.build_variant = "Debug"

    if args.anthem_build_variant is None:
        args.anthem_build_variant = args.build_variant

    if args.sdl_build_variant is None:
        args.sdl_build_variant = args.build_variant

    # Assertions are enabled by default.
    if args.assertions is None:
        args.assertions = True

    # Propagate the default assertions setting.
    if args.anthem_assertions is None:
        args.anthem_assertions = args.assertions

    if args.libcxx_assertions is None:
        args.libcxx_assertions = args.assertions

    if args.std is None:
        args.std = "c++14"

    if args.stdlib is None and args.main_tool == "llvm":
        args.stdlib = "libc++"
    if (args.build_llvm or args.build_libcxx) and args.stdlib is None:
        args.stdlib = "libc++"

    # Set the default CMake generator.
    if args.cmake_generator is None:
        args.cmake_generator = "Ninja"

    if not args.auth_token and ("CI" not in os.environ or not os.environ["CI"]):
        with open(args.auth_token_file) as token_file:
            args.auth_token = str(token_file.read())

    if args.executable_name is None:
        args.executable_name = "anthem-{}".format(args.host_target)

    if args.lib_name is None:
        args.lib_name = "anthem-lib-{}".format(args.host_target)

    if args.test_executable_name is None:
        args.test_executable_name = "anthem-test-{}".format(args.host_target)


def create_argument_parser():
    """
    Return a configured argument parser.
    """

    # NOTE: USAGE, DESCRIPTION and EPILOGUE are defined at the bottom of
    # the file
    parser = _ApplyDefaultsArgumentParser(
        apply_defaults=_apply_default_arguments,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        usage=USAGE,
        description=DESCRIPTION,
        epilog=EPILOGUE
    )

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
        default=os.path.join(ANTHEM_SOURCE_ROOT, "dest"),
        help="the installation prefix. This is where built Unsung Anthem "
             "products (like bin, lib, and include) will be installed.")

    option(
        ["-j", "--jobs"],
        store_int("build_jobs"),
        default=multiprocessing.cpu_count(),
        help="the number of parallel build jobs to use")

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
        "--msbuild",
        store_path(executable=True),
        help="the absolute path to MSBuild for the host platform. Default is "
             "auto detected")

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
        "--extra-cmake-options",
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
    option(
        ["-t", "--test"],
        toggle_true("build_test"),
        help="build the Unsung Anthem tests")

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

    option(
        "--visual-studio-14",
        store("cmake_generator"),
        const="Visual Studio 14 2015",
        help="use CMake's Visual Studio 2015 generator (%(default)s by "
             "default)")

    option(
        "--visual-studio-15",
        store("cmake_generator"),
        const="Visual Studio 15 2017",
        help="use CMake's Visual Studio 2017 generator (%(default)s by "
             "default)")

    # -------------------------------------------------------------------------
    in_group("Extra actions to perform before or in addition to building")

    option(["-c", "--clean"], store_true, help="do a clean build")

    option(
        "--gcov",
        store_true("enable_gcov"),
        help="use gcov and lcov to generate code coverage information"
    )

    # -------------------------------------------------------------------------
    in_group("Build variant")

    with mutually_exclusive_group():

        set_defaults(build_variant="Debug")

        option(
            ["-d", "--debug"],
            store("build_variant"),
            const="Debug",
            help="build the Debug variant of Unsung Anthem and related "
                 "project (default is %(default)s)")

        option(
            ["-r", "--release-debuginfo"],
            store("build_variant"),
            const="RelWithDebInfo",
            help="build the RelWithDebInfo variant of Unsung Anthem and "
                 "related project (default is %(default)s)")

        option(
            ["-R", "--release"],
            store("build_variant"),
            const="Release",
            help="build the Release variant of Unsung Anthem and related "
                 "project (default is %(default)s)")

    # -------------------------------------------------------------------------
    in_group("Override build variant for a specific project")

    option(
        "--debug-anthem",
        store("anthem_build_variant"),
        const="Debug",
        help="build the Debug variant of Unsung Anthem")

    option(
        "--debug-sdl",
        store("sdl_build_variant"),
        const="Debug",
        help="build the Debug variant of Simple DirectMedia Layer")

    # -------------------------------------------------------------------------
    # Assertions group

    with mutually_exclusive_group():

        set_defaults(assertions=True)

        # TODO: Convert to store_true
        option(
            "--assertions",
            store,
            const=True,
            help="enable assertions in all projects")

        # TODO: Convert to store_false
        option(
            "--no-assertions",
            store("assertions"),
            const=False,
            help="disable assertions in all projects")

    # -------------------------------------------------------------------------
    in_group("Control assertions in a specific project")

    option(
        "--anthem-assertions",
        store,
        const=True,
        help="enable assertions in Unsung Anthem")
    option(
        "--libcxx-assertions",
        store,
        const=True,
        help="enable assertions in libc++ if it is built")

    # -------------------------------------------------------------------------
    in_group("Authentication options")

    with mutually_exclusive_group():

        option(
            "--auth-token-file",
            store,
            default=os.path.join(
                ANTHEM_SOURCE_ROOT,
                ANTHEM_REPO_NAME,
                "token"),
            metavar="TOKEN",
            help="the file which contains the OAuth token which is used to "
                 "access the GitHub API")

        option(
            "--auth-token",
            store,
            metavar="TOKEN",
            help="the OAuth token which is used to access the GitHub API")

    # -------------------------------------------------------------------------
    in_group("Program options")

    option(
        "--executable-name",
        store,
        help="the name of the Unsung Anthem executable"
    )
    option(
        "--lib-name",
        store,
        help="the name of the Unsung Anthem library binaries"
    )
    option(
        "--test-executable-name",
        store,
        help="the name of the Unsung Anthem test executable"
    )

    # -------------------------------------------------------------------------
    in_group("Threading options")

    with mutually_exclusive_group():
        set_defaults(multithreading=True)

        # TODO: Convert to store_true
        option(
            "--multithreading",
            store("multithreading"),
            const=True,
            help="use multithreading in the game")

        # TODO: Convert to store_false
        option(
            "--no-multithreading",
            store("multithreading"),
            const=False,
            help="use single thread in the game")

        # TODO: Convert to store_false
        option(
            "--single-thread",
            store("multithreading"),
            const=False,
            help="use single thread in the game")

    # -------------------------------------------------------------------------
    in_group("MSBuild options")

    option(
        "--msbuild-logger",
        store_path,
        help="the absolute path to MSBuild logger",
        metavar="PATH")

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
