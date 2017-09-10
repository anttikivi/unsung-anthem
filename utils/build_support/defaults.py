#===-------------------------- defaults.py -------------------*- python -*-===#
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
        if not args.sdl and not args.glfw:
            args.sdl = False
            args.glfw = True

    def _implicit_llvm():
        if args.llvm_build_variant is not None \
                or args.llvm_assertions is not None:
            args.build_llvm = True

    def _build_variant(default_value):
        if args.build_variant is None:
            args.build_variant = default_value
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
        if args.llvm_assertions is None:
            args.llvm_assertions = args.assertions
        if args.libcxx_assertions is None:
            args.libcxx_assertions = args.assertions
        if args.anthem_assertions is None:
            args.anthem_assertions = args.assertions

    def _cmake_generator(default_value):
        if args.cmake_generator is None:
            args.cmake_generator = default_value
        if args.enable_gcov:
            args.cmake_generator = "Unix Makefiles"
        if args.clion:
            args.cmake_generator = "Unix Makefiles"

    def _tests():
        if args.test_only:
            args.clean = False

        if args.clion:
            args.test = False
            args.test_optimized = False
            args.build_test = False
            args.build_test_optimized = False
        if args.test_optimized:
            args.test = True
            args.build_test_optimized = True
        if args.test:
            args.build_test = True

    def _building():
        if not args.build_ninja \
                and args.cmake_generator == "Visual Studio 14 2015":
            args.build_ninja = False
        if args.skip_build:
            args.skip_build_anthem = True
            args.build_llvm = False
            args.build_libcxx = False
            args.build_cmake = False
            args.build_ninja = False
            args.build_test = False
            args.build_test_optimized = False
        if args.build_llvm:
            args.build_libcxx = False

    def _shared_builds():
        if args.disable_shared_builds:
            args.share_builds = False
        else:
            args.share_builds = True

    def _visual_studio():
        args.visual_studio = args.cmake_generator.startswith("Visual Studio")

    _build_actions()
    _sdl_glfw()
    _implicit_llvm()
    _build_variant("Debug")
    _assertions(True)
    _cmake_generator("Ninja")
    _tests()
    _building()
    _shared_builds()
    _visual_studio()


def cxx_std(args):
    """
    Apply the default C++ argument values to the arguments.

    args -- the command line argument dictionary.
    """
    if args.stdlib is None and args.main_tool == "llvm":
        args.stdlib = "libc++"
    if (args.build_llvm or args.build_libcxx) and args.stdlib is None:
        args.stdlib = "libc++"


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
        patch=int(args.cmake_version.split(".")[2]),
        patch_minor=0
    )

    if len(args.cmake_version.split(".")) == 4:
        args.cmake_version_mapping.patch_minor = int(
            args.cmake_version.split(".")[3]
        )


def file_arguments(args):
    """
    Apply the default file-related arguments.

    args -- the command line arguments.
    """
    if args.build_subdir is None:
        args.build_subdir = compute_build_subdir(args)
    if not args.share_builds:
        args.shared_build_subdir = args.build_subdir
    else:
        if args.shared_build_subdir is None:
            args.shared_build_subdir = compute_shared_build_subdir(args)
    if args.install_prefix is None:
        if not args.share_builds:
            args.install_prefix = compute_install_prefix(args)
        else:
            args.install_prefix = compute_shared_install_prefix(args)
    if args.executable_name is None:
        args.executable_name = "unsung-anthem-{}".format(args.host_target)
    if args.test_executable_name is None:
        args.test_executable_name = "test-{}".format(args.executable_name)


def skip_repositories(args, toolchain):
    """
    Create the list of the repositories which are skipped by default in the
    checkout.

    args -- the command line argument dictionary.
    """
    if not args.build_llvm:
        if not args.build_libcxx:
            args.skip_repository_list += ["llvm"]
        else:
            args.skip_repository_list += ["llvm-clang"]
            args.skip_repository_list += ["llvm-llvm"]

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


def authorization(args):
    """
    Apply the default authorization argument values to the arguments.

    args -- the command line argument dictionary.
    """
    if not args.auth_token and not args.ci:
        with open(args.auth_token_file) as token_file:
            args.auth_token = str(token_file.read())
