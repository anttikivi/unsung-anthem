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


import json


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
            with open(args.build_config) as json_file:
                config = json.load(json_file)

            asset_node = config["dependencies"]["gcc"]["asset"]
            args.gcc_mirror = asset_node["default_mirror"]

    def _shared_builds():
        if args.disable_shared_builds:
            args.share_builds = False
        else:
            args.share_builds = True

    def _visual_studio():
        # Set the Visual Studio option to true if the CMake generator is
        # Visual Studio.
        if args.cmake_generator.startswith("Visual Studio"):
            args.visual_studio = True
        else:
            args.visual_studio = False

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


def add_version_info(args, name, dependencies):
    """
    Add version information to the arguments.
    """
    if getattr(args, "{}_version".format(name)) == "default":
        node = dependencies[name]
        setattr(args, "{}_version".format(name), node["default_version"])

    # TODO This might be unnecessary:
    # args.version_info["gcc"] = args.gcc_version


def default_versions(args):
    def _llvm():
        if args.llvm_version == "default":
            llvm_node = dependencies["llvm"]
            args.llvm_version = llvm_node["default_version"]

            if args.llvm_version == "git":
                args.llvm_version = "6.0.0svn"

        args.version_info["llvm"] = args.llvm_version

    def _gcc():
        if args.gcc_version == "default":
            gcc_node = dependencies["gcc"]
            args.gcc_version = gcc_node["default_version"]

        args.version_info["gcc"] = args.gcc_version

    def _cmake():
        def _version_branches():
            if args.cmake_major_version == "default":
                args.cmake_major_version = \
                    int(cmake_node["default_version"]["major"])

            if args.cmake_minor_version == "default":
                args.cmake_minor_version = \
                    int(cmake_node["default_version"]["minor"])

            if args.cmake_patch_version == "default":
                args.cmake_patch_version = \
                    int(cmake_node["default_version"]["patch"])

            if args.cmake_minor_patch_version == "default":
                if "minor_patch" in cmake_node["default_version"]:
                    try:
                        minor_patch = \
                            int(cmake_node["default_version"]["minor_patch"])

                        if minor_patch == 0:
                            args.cmake_minor_patch_version = None
                        else:
                            args.cmake_minor_patch_version = minor_patch
                    except ValueError:
                        args.cmake_minor_patch_version = None

        cmake_node = dependencies["cmake"]

        if args.cmake_version == "default":
            _version_branches()

            if args.cmake_minor_patch_version is None:
                args.cmake_version = "{}.{}.{}".format(
                    args.cmake_major_version,
                    args.cmake_minor_version,
                    args.cmake_patch_version)
            else:
                args.cmake_version = "{}.{}.{}.{}".format(
                    args.cmake_major_version,
                    args.cmake_minor_version,
                    args.cmake_patch_version,
                    args.cmake_minor_patch_version)
        else:
            if len(args.cmake_version.split(".")) == 3:
                args.cmake_major_version = \
                    int(args.cmake_version.split(".")[0])
                args.cmake_minor_version = \
                    int(args.cmake_version.split(".")[1])
                args.cmake_patch_version = \
                    int(args.cmake_version.split(".")[2])
            elif len(args.cmake_version.split(".")) == 4:
                args.cmake_major_version = \
                    int(args.cmake_version.split(".")[0])
                args.cmake_minor_version = \
                    int(args.cmake_version.split(".")[1])
                args.cmake_patch_version = \
                    int(args.cmake_version.split(".")[2])
                args.cmake_minor_patch_version = \
                    int(args.cmake_version.split(".")[3])

        args.version_info["cmake"] = args.cmake_version

        args.version_info["cmake_info"] = {
            "major": args.cmake_major_version,
            "minor": args.cmake_minor_version,
            "patch": args.cmake_patch_version
        }

    def _ninja():
        if args.ninja_version == "default":
            ninja_node = dependencies["ninja"]
            args.ninja_version = ninja_node["default_version"]

        args.version_info["ninja"] = args.ninja_version

    def _catch():
        if args.catch_version == "default":
            catch_node = dependencies["catch"]
            args.catch_version = catch_node["default_version"]

        args.version_info["catch"] = args.catch_version

    with open(args.build_config) as json_file:
        config = json.load(json_file)

    if args.anthem_version == "default":
        args.anthem_version = config["version"]

    args.version_info["anthem"] = args.anthem_version

    dependencies = config["dependencies"]

    add_version_info(args, "llvm", dependencies)
    add_version_info(args, "gcc", dependencies)
    add_version_info(args, "cmake", dependencies)
    add_version_info(args, "ninja", dependencies)
    add_version_info(args, "catch", dependencies)
    add_version_info(args, "sdl", dependencies)
    add_version_info(args, "glfw", dependencies)
    add_version_info(args, "spdlog", dependencies)
    add_version_info(args, "cat", dependencies)

    _llvm()
    _gcc()
    _cmake()
    _ninja()
    _catch()
