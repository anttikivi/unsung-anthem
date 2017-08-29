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


from .config import PRODUCT_CONFIG

from .products.product_config import version_config

from .workspace import \
    compute_build_subdir, compute_install_prefix, \
    compute_shared_build_subdir, compute_shared_install_prefix


def fix_main_tool(args):
    """
    Set the main tool arguments to 'llvm' if it is set to 'clang'.

    This function does modify the parameter passed in.

    args -- the arguments to which the values are set.
    """
    # LLVM and Clang are synonyms as main tools.
    if args.main_tool == "clang":
        args.main_tool = "llvm"

    return args


def main_args(args):
    """
    Set the default arguments to the 'args' namespace.

    This function does modify the parameter passed in.

    args -- the arguments to which the values are set.
    """
    def _build_actions():
        if args.install_only:
            args.build_only = False
            args.test_only = False
            args.docs_only = False
        elif args.build_only:
            args.install_only = False
            args.test_only = False
            args.docs_only = False
        elif args.test_only:
            args.build_only = False
            args.install_only = False
            args.docs_only = False
        elif args.docs_only:
            args.build_only = False
            args.install_only = False
            args.test_only = False

    def _sdl_glfw():
        # If SDL or GLFW is not explicitly specified, use GLFW.
        if not args.sdl and not args.glfw:
            args.sdl = False
            args.glfw = True

    def _implicit_llvm():
        # Build LLVM if any LLVM-related options were specified.
        if args.llvm_build_variant is not None \
                or args.llvm_assertions is not None:
            args.build_llvm = True

    def _build_variant(default_value):
        if args.build_variant is None:
            args.build_variant = default_value

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

    def _assertions(default_value):
        if args.assertions is None:
            args.assertions = default_value

        # Propagate the assertion option.
        if args.llvm_assertions is None:
            args.llvm_assertions = args.assertions

        if args.libcxx_assertions is None:
            args.libcxx_assertions = args.assertions

        if args.anthem_assertions is None:
            args.anthem_assertions = args.assertions

    def _cmake_generator(default_value):
        if args.cmake_generator is None:
            args.cmake_generator = default_value

        # The only CMake generator with gcov is make.
        if args.enable_gcov:
            args.cmake_generator = "Unix Makefiles"

        # The default CMake generator on CLion is make.
        if args.clion:
            args.cmake_generator = "Unix Makefiles"

    def _tests():
        # Propagate --run-test.
        if args.test_only:
            args.clean = False

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

    def _building():
        # By default, Ninja is not built on AppVeyor.
        if not args.build_ninja \
                and args.cmake_generator == "Visual Studio 14 2015":
            args.build_ninja = False

        # Propagate global --skip-build.
        if args.skip_build:
            args.skip_build_anthem = True
            args.build_llvm = False
            args.build_gcc = False
            args.build_libcxx = False
            args.build_cmake = False
            args.build_ninja = False
            args.build_test = False
            args.build_test_optimized = False

        # If the LLVM is built, there is no need for explicitly building
        # libc++.
        if args.build_llvm:
            args.build_libcxx = False

    def _gcc_mirror():
        # Set the default GCC mirror.
        if args.gcc_mirror == "default":
            args.gcc_mirror = PRODUCT_CONFIG.gcc.default_mirror

    def _shared_builds():
        if args.disable_shared_builds:
            args.share_builds = False
        else:
            args.share_builds = True

    def _visual_studio():
        # Set the Visual Studio option to true if the CMake generator is
        # Visual Studio.
        args.visual_studio = args.cmake_generator.startswith("Visual Studio")

    # Add the build action arguments.
    _build_actions()

    # Add the SDL vs. GLFW arguments.
    _sdl_glfw()

    # Add the arguments for building LLVM implicitly.
    _implicit_llvm()

    # Add the build variant options. The default build variant is 'Debug'.
    _build_variant("Debug")

    # Add the assertion arguments. Assertions are enabled by default.
    _assertions(True)

    # Add the CMake generator arguments. The default argument is 'Ninja'.
    _cmake_generator("Ninja")

    # Add the test-enabling arguments.
    _tests()

    # Add the arguments for deciding which projects are built.
    _building()

    # Add the GCC mirror arguments.
    _gcc_mirror()

    # Add the shared builds arguments.
    _shared_builds()

    # Add the Visual Studio arguments.
    _visual_studio()


def cxx_std(args):
    """
    Apply the default C++ argument values to the arguments.

    args -- the command line argument dictionary.
    """
    # If the build is done in a CI environment and the compiler is Clang,
    # default to libc++.
    if args.stdlib is None and args.ci and args.main_tool == "llvm":
        args.stdlib = "libc++"

    # If LLVM or libc++ is being built, the library should be set to libc++.
    if (args.build_llvm or args.build_libcxx) and args.stdlib is None:
        args.stdlib = "libc++"

    # If GCC is being built, the library should be set to libstdc++.
    if args.build_gcc and args.stdlib is None:
        args.stdlib = "libstdc++"

    # Set the C++ standard library implementation and a flag denoting whether
    # or not it is set.
    if args.stdlib is None:
        args.stdlib_set = False
    else:
        args.stdlib_set = True

    if args.std == "latest":
        args.std = "c++latest"


def default_versions(args):
    """
    Apply the default version argument values to the arguments.

    args -- the command line argument dictionary.
    """

    if args.llvm_version == "git":
        args.llvm_version = PRODUCT_CONFIG.llvm.git_version

    args.cmake_version_mapping = version_config(
        major=int(args.cmake_version.split(".")[0]),
        minor=int(args.cmake_version.split(".")[1]),
        patch=int(args.cmake_version.split(".")[2])
    )

    if len(args.cmake_version.split(".")) == 4:
        args.cmake_version_mapping.patch_minor = int(
            args.cmake_version.split(".")[3]
        )


def file_arguments(args):
    # Set the build subdirectory.
    if args.build_subdir is None:
        args.build_subdir = compute_build_subdir(args)

    # Set the shared build subdirectory.
    if not args.share_builds:
        args.shared_build_subdir = args.build_subdir
    else:
        if args.shared_build_subdir is None:
            args.shared_build_subdir = compute_shared_build_subdir(args)

    # Set the installation subdirectory.
    if args.install_prefix is None:
        if not args.share_builds:
            args.install_prefix = compute_install_prefix(args)
        else:
            args.install_prefix = compute_shared_install_prefix(args)

    # Set the executable name.
    if args.executable_name is None:
        args.executable_name = "unsung-anthem-{}".format(args.host_target)

    # Set the test executable name.
    if args.test_executable_name is None:
        args.test_executable_name = "test-{}".format(args.executable_name)


def skip_repositories(args, toolchain):
    if not args.build_llvm:
        if not args.build_libcxx:
            args.skip_repository_list += ["llvm"]
        else:
            args.skip_repository_list += ["llvm-clang"]
            args.skip_repository_list += ["llvm-llvm"]

    if not args.build_gcc:
        args.skip_repository_list += ["gcc"]

    if not args.build_cmake and toolchain.cmake is not None:
        args.skip_repository_list += ["cmake"]

    if not args.build_ninja and toolchain.ninja is not None:
        args.skip_repository_list += ["ninja"]

    if not args.build_test:
        args.skip_repository_list += ["catch"]

    if not args.sdl:
        args.skip_repository_list += ["sdl"]

    if not args.glfw:
        args.skip_repository_list += ["glfw"]
