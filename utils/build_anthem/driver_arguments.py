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

import multiprocessing

import android.adb.commands

from swift_build_support.swift_build_support import host
from swift_build_support.swift_build_support import targets
from swift_build_support.swift_build_support.targets import \
    StdlibDeploymentTarget

from . import argparse
from . import defaults


__all__ = [
    'create_argument_parser',
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

    # Build cmark if any cmark-related options were specified.
    if (args.cmark_build_variant is not None):
        args.build_cmark = True

    # Build LLDB if any LLDB-related options were specified.
    if args.lldb_build_variant is not None or \
       args.lldb_assertions is not None:
        args.build_lldb = True

    # Set the default build variant.
    if args.build_variant is None:
        args.build_variant = 'Debug'

    if args.llvm_build_variant is None:
        args.llvm_build_variant = args.build_variant

    if args.swift_build_variant is None:
        args.swift_build_variant = args.build_variant

    if args.swift_stdlib_build_variant is None:
        args.swift_stdlib_build_variant = args.build_variant

    if args.cmark_build_variant is None:
        args.cmark_build_variant = args.swift_build_variant

    if args.lldb_build_variant is None:
        args.lldb_build_variant = args.build_variant

    if args.foundation_build_variant is None:
        args.foundation_build_variant = args.build_variant

    if args.libdispatch_build_variant is None:
        args.libdispatch_build_variant = args.build_variant

    if args.libicu_build_variant is None:
        args.libicu_build_variant = args.build_variant

    # Assertions are enabled by default.
    if args.assertions is None:
        args.assertions = True

    # Propagate the default assertions setting.
    if args.cmark_assertions is None:
        args.cmark_assertions = args.assertions

    if args.llvm_assertions is None:
        args.llvm_assertions = args.assertions

    if args.swift_assertions is None:
        args.swift_assertions = args.assertions

    if args.swift_stdlib_assertions is None:
        args.swift_stdlib_assertions = args.assertions

    # Set the default CMake generator.
    if args.cmake_generator is None:
        args.cmake_generator = 'Ninja'

    # --ios-all etc are not supported by open-source Swift.
    if args.ios_all:
        raise ValueError('error: --ios-all is unavailable in open-source '
                         'Swift.\nUse --ios to skip iOS device tests.')

    if args.tvos_all:
        raise ValueError('error: --tvos-all is unavailable in open-source '
                         'Swift.\nUse --tvos to skip tvOS device tests.')

    if args.watchos_all:
        raise ValueError('error: --watchos-all is unavailable in open-source '
                         'Swift.\nUse --watchos to skip watchOS device tests.')

    # Propagate global --skip-build
    if args.skip_build:
        args.build_linux = False
        args.build_freebsd = False
        args.build_cygwin = False
        args.build_osx = False
        args.build_ios = False
        args.build_tvos = False
        args.build_watchos = False
        args.build_android = False
        args.build_benchmarks = False
        args.build_external_benchmarks = False
        args.build_lldb = False
        args.build_llbuild = False
        args.build_swiftpm = False
        args.build_xctest = False
        args.build_foundation = False
        args.build_libdispatch = False
        args.build_libicu = False
        args.build_playgroundlogger = False
        args.build_playgroundsupport = False

    # --skip-{ios,tvos,watchos} or --skip-build-{ios,tvos,watchos} are
    # merely shorthands for --skip-build-{**os}-{device,simulator}
    if not args.ios or not args.build_ios:
        args.build_ios_device = False
        args.build_ios_simulator = False

    if not args.tvos or not args.build_tvos:
        args.build_tvos_device = False
        args.build_tvos_simulator = False

    if not args.watchos or not args.build_watchos:
        args.build_watchos_device = False
        args.build_watchos_simulator = False

    if not args.android or not args.build_android:
        args.build_android = False

    # --validation-test implies --test.
    if args.validation_test:
        args.test = True

    # --test-optimized implies --test.
    if args.test_optimized:
        args.test = True

    # --test-optimize-size implies --test.
    if args.test_optimize_for_size:
        args.test = True

    # If none of tests specified skip swift stdlib test on all platforms
    if not args.test and not args.validation_test and not args.long_test:
        args.test_linux = False
        args.test_freebsd = False
        args.test_cygwin = False
        args.test_osx = False
        args.test_ios = False
        args.test_tvos = False
        args.test_watchos = False

    # --skip-test-ios is merely a shorthand for host and simulator tests.
    if not args.test_ios:
        args.test_ios_host = False
        args.test_ios_simulator = False
    # --skip-test-tvos is merely a shorthand for host and simulator tests.
    if not args.test_tvos:
        args.test_tvos_host = False
        args.test_tvos_simulator = False
    # --skip-test-watchos is merely a shorthand for host and simulator
    # --tests.
    if not args.test_watchos:
        args.test_watchos_host = False
        args.test_watchos_simulator = False

    # --skip-build-{ios,tvos,watchos}-{device,simulator} implies
    # --skip-test-{ios,tvos,watchos}-{host,simulator}
    if not args.build_ios_device:
        args.test_ios_host = False
    if not args.build_ios_simulator:
        args.test_ios_simulator = False

    if not args.build_tvos_device:
        args.test_tvos_host = False
    if not args.build_tvos_simulator:
        args.test_tvos_simulator = False

    if not args.build_watchos_device:
        args.test_watchos_host = False
    if not args.build_watchos_simulator:
        args.test_watchos_simulator = False

    if not args.build_android:
        args.test_android_host = False

    if not args.host_test:
        args.test_ios_host = False
        args.test_tvos_host = False
        args.test_watchos_host = False
        args.test_android_host = False


def create_argument_parser():
    """Return a configured argument parser."""

    # NOTE: USAGE, DESCRIPTION and EPILOG are defined at the bottom of the file
    parser = _ApplyDefaultsArgumentParser(
        apply_defaults=_apply_default_arguments,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        usage=USAGE,
        description=DESCRIPTION,
        epilog=EPILOG)

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

    return builder.build()


# ----------------------------------------------------------------------------

USAGE = """
  %(prog)s [-h | --help] [OPTION ...]
  %(prog)s --preset=NAME [SUBSTITUTION ...]
"""


DESCRIPTION = """
Use this tool to build, test, and prepare binary distribution archives of Swift
and related tools.

Builds Swift (and, optionally, LLDB), incrementally, optionally
testing it thereafter.  Different build configurations are maintained in
parallel.
"""


EPILOG = """
Using option presets:

  --preset-file=PATH    load presets from the specified file

  --preset=NAME         use the specified option preset

  The preset mode is mutually exclusive with other options.  It is not
  possible to add ad-hoc customizations to a preset.  This is a deliberate
  design decision.  (Rationale: a preset is a certain important set of
  options that we want to keep in a centralized location.  If you need to
  customize it, you should create another preset in a centralized location,
  rather than scattering the knowledge about the build across the system.)

  Presets support substitutions for controlled customizations.  Substitutions
  are defined in the preset file.  Values for substitutions are supplied
  using the name=value syntax on the command line.


Any arguments not listed are forwarded directly to Swift's
'build-script-impl'.  See that script's help for details.

Environment variables
---------------------

This script respects a few environment variables, should you
choose to set them:

SWIFT_SOURCE_ROOT: a directory containing the source for LLVM, Clang, Swift.
                   If this script is located in a Swift
                   source directory, the location of SWIFT_SOURCE_ROOT will be
                   inferred if the variable is not set.

'build-script' expects the sources to be laid out in the following way:

   $SWIFT_SOURCE_ROOT/llvm
                     /clang
                     /swift
                     /lldb                       (optional)
                     /llbuild                    (optional)
                     /swiftpm                    (optional, requires llbuild)
                     /compiler-rt                (optional)
                     /swift-corelibs-xctest      (optional)
                     /swift-corelibs-foundation  (optional)
                     /swift-corelibs-libdispatch (optional)
                     /icu                        (optional)

SWIFT_BUILD_ROOT: a directory in which to create out-of-tree builds.
                  Defaults to "$SWIFT_SOURCE_ROOT/build/".

Preparing to run this script
----------------------------

  See README.md for instructions on cloning Swift subprojects.

If you intend to use the -l, -L, --lldb, or --debug-lldb options.

That's it; you're ready to go!

Examples
--------

Given the above layout of sources, the simplest invocation of 'build-script' is
just:

  [~/src/s]$ ./swift/utils/build-script

This builds LLVM, Clang, Swift and Swift standard library in debug mode.

All builds are incremental.  To incrementally build changed files, repeat the
same 'build-script' command.

Typical uses of 'build-script'
------------------------------

To build everything with optimization without debug information:

  [~/src/s]$ ./swift/utils/build-script -R

To run tests, add '-t':

  [~/src/s]$ ./swift/utils/build-script -R -t

To run normal tests and validation tests, add '-T':

  [~/src/s]$ ./swift/utils/build-script -R -T

To build LLVM+Clang with optimization without debug information, and a
debuggable Swift compiler:

  [~/src/s]$ ./swift/utils/build-script -R --debug-swift

To build a debuggable Swift standard library:

  [~/src/s]$ ./swift/utils/build-script -R --debug-swift-stdlib

iOS build targets are always configured and present, but are not built by
default.  To build the standard library for OS X, iOS simulator and iOS device:

  [~/src/s]$ ./swift/utils/build-script -R -i

To run OS X and iOS tests that don't require a device:

  [~/src/s]$ ./swift/utils/build-script -R -i -t

To use 'make' instead of 'ninja', use '-m':

  [~/src/s]$ ./swift/utils/build-script -m -R

To create Xcode projects that can build Swift, use '-x':

  [~/src/s]$ ./swift/utils/build-script -x -R

Preset mode in build-script
---------------------------

All buildbots and automated environments use 'build-script' in *preset mode*.
In preset mode, the command line only specifies the preset name and allows
limited customization (extra output paths).  The actual options come from
the selected preset in 'utils/build-presets.ini'.  For example, to build like
the incremental buildbot, run:

  [~/src/s]$ ./swift/utils/build-script --preset=buildbot_incremental

To build with AddressSanitizer:

  [~/src/s]$ ./swift/utils/build-script --preset=asan

To build a root for Xcode XYZ, '/tmp/xcode-xyz-root.tar.gz':

  [~/src/s]$ ./swift/utils/build-script --preset=buildbot_BNI_internal_XYZ \\
      install_destdir="/tmp/install"
      install_symroot="/tmp/symroot"
      installable_package="/tmp/xcode-xyz-root.tar.gz"

If you have your own favorite set of options, you can create your own, local,
preset.  For example, let's create a preset called 'ds' (which stands for
Debug Swift):

  $ cat > ~/.swift-build-presets
  [preset: ds]
  release
  debug-swift
  debug-swift-stdlib
  test
  build-subdir=ds

To use it, specify the '--preset=' argument:

  [~/src/s]$ ./swift/utils/build-script --preset=ds
  ./swift/utils/build-script: using preset 'ds', which expands to
  ./swift/utils/build-script --release --debug-swift --debug-swift-stdlib \
     --test
  --build-subdir=ds --
  ...

Existing presets can be found in `utils/build-presets.ini`

Philosophy
----------

While you can invoke CMake directly to build Swift, this tool will save you
time by taking away the mechanical parts of the process, providing you controls
for the important options.

For all automated build environments, this tool is regarded as *the* *only* way
to build Swift.  This is not a technical limitation of the Swift build system.
It is a policy decision aimed at making the builds uniform across all
environments and easily reproducible by engineers who are not familiar with the
details of the setups of other systems or automated environments.
"""
