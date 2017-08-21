#===-------------------------- defaults.py --------------------*- python -*-===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

"""
The support module for applying the default values of the command line
arguments.
"""


def main_args(args):
    if args.install_only:
        args.build_only = False
        args.test_only = False
        args.update_checkout_only = False
        args.docs_only = False
    elif args.build_only:
        args.install_only = False
        args.test_only = False
        args.update_checkout_only = False
        args.docs_only = False
    elif args.test_only:
        args.build_only = False
        args.install_only = False
        args.update_checkout_only = False
        args.docs_only = False
    elif args.update_checkout_only:
        args.build_only = False
        args.install_only = False
        args.test_only = False
        args.docs_only = False
    elif args.docs_only:
        args.build_only = False
        args.install_only = False
        args.test_only = False
        args.update_checkout_only = False

    # If SDL or GLFW is not explicitly specified, use GLFW.
    if not args.sdl and not args.glfw:
        args.sdl = False
        args.glfw = True

    # Build LLVM if any LLVM-related options were specified.
    if args.llvm_build_variant is not None or args.llvm_assertions is not None:
        args.build_llvm = True

    # The default build variant is Debug.
    if args.build_variant is None:
        args.build_variant = 'Debug'

    # Propagate the build variant.
    if args.llvm_build_variant is None:
        args.llvm_build_variant = args.build_variant

    if args.libcxx_build_variant is None:
        args.libcxx_build_variant = args.build_variant

    if args.anthem_build_variant is None:
        args.anthem_build_variant = args.build_variant

    if args.sdl_build_variant is None:
        args.sdl_build_variant = args.build_variant

    if args.glfw_build_variant is None:
        args.glfw_build_variant = args.build_variant

    # Assertions are enabled by default.
    if args.assertions is None:
        args.assertions = True

    # Propagate the assertion option.
    if args.llvm_assertions is None:
        args.llvm_assertions = args.assertions

    if args.libcxx_assertions is None:
        args.libcxx_assertions = args.assertions

    if args.anthem_assertions is None:
        args.anthem_assertions = args.assertions

    # The default CMake generator is Ninja.
    if args.cmake_generator is None:
        args.cmake_generator = 'Ninja'

    # The only CMake generator with gcov is make.
    if args.enable_gcov:
        args.cmake_generator = 'Unix Makefiles'

    # The default CMake generator on CLion is make.
    if args.clion:
        args.cmake_generator = 'Unix Makefiles'

    # Propagate --run-test.
    if args.test_only:
        args.clean = False
        args.clean_build = False

    # Propagate --clean.
    if args.clean:
        args.clean_build = True
        args.clean_shared = True

    if args.clion:
        args.test = False
        args.test_optimized = False
        args.build_test = False
        args.build_test_optimized = False

    # --test-optimized implies --test and --build-test-optimized.
    if args.test_optimized:
        args.test = True
        args.build_test_optimized = True

    # --test implies --build-test.
    if args.test:
        args.build_test = True

    # By default, Ninja is not built on AppVeyor.
    if not args.build_ninja \
            and args.cmake_generator == 'Visual Studio 14 2015':
        args.build_ninja = False

    # Propagate global --skip-build
    if args.skip_build:
        args.skip_build_anthem = True
        args.build_llvm = False
        args.build_gcc = False
        args.build_libcxx = False
        args.build_cmake = False
        args.build_ninja = False
        args.build_test = False
        args.build_test_optimized = False

    # If the LLVM is built, there is no need for explicitly building libc++.
    if args.build_llvm:
        args.build_libcxx = False

    # Set the default GCC mirror.
    if args.gcc_mirror == 'default':
        with open(args.build_config) as f:
            config = json.load(f)

        asset_node = config['dependencies']['gcc']['asset']
        args.gcc_mirror = asset_node['default_mirror']

    if args.disable_shared_tools:
        args.share_tools = False
    else:
        args.share_tools = True

    # Set the Visual Studio option to true if the CMake generator is Visual
    # Studio.
    if args.cmake_generator.startswith('Visual Studio'):
        args.visual_studio = True
    else:
        args.visual_studio = False


def cxx_std(args):
    """
    Apply the default C++ argument values to the arguments.

    args -- the command line argument dictionary.
    """
    # If the build is done in a CI environment and the compiler is Clang,
    # default to libc++.
    if args.stdlib is None and args.ci and args.main_tool == 'llvm':
        args.stdlib = 'libc++'

    # If LLVM or libc++ is being built, the library should be set to libc++.
    if (args.build_llvm or args.build_libcxx) and args.stdlib is None:
        args.stdlib = 'libc++'

    # If GCC is being built, the library should be set to libstdc++.
    if args.build_gcc and args.stdlib is None:
        args.stdlib = 'libstdc++'

    # Set the C++ standard library implementation and a flag denoting whether
    # or not it is set.
    if args.stdlib is None:
        args.stdlib_set = False
    else:
        args.stdlib_set = True
