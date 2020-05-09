# Building Obliging Ode and Unsung Anthem

Whether you want to contribute to Obliging Ode and Unsung Anthem or simply try out the latest and greatest features of the projects, you need to build the projects from source. Luckily it’s quite simple. The building process for each officially supported platform is explained in this document.

#### Table of Contents

[Prerequisites](#prerequisites)

[Building](#building)
* [Linux](#linux)
* [macOS](#macos)
* [Windows](#windows)

[Configuring the Build](#configuring-the-build)

[Command Line Options](#command-line-options)
* [Common Top-level Options](#common-top-level-options)
  * [Special Options](#special-options)
  * [Top-level Options](#top-level-options)
  * [GitHub Options](#github-options)
* [Common Options](#common-options)
  * [Build Variant Options](#build-variant-options)
  * [Build Target Options](#build-target-options)
  * [Toolchain Options](#toolchain-options)
  * [OpenGL Options](#opengl-options)
  * [Build Generator Options](#build-generator-options)
* [Preset Mode Options](#preset-mode-options)
* [Configuring Mode Options](#configuring-mode-options)
* [Composing Mode Options](#composing-mode-options)
  * [Compose: Common Options](#compose-common-options)
  * [Compose: C++ Standard Options](#compose-c-standard-options)
  * [Compose: Feature Options](#compose-feature-options)

[Environment Variables](#environment-variables)

## Prerequisites

To build Obliging Ode and Unsung Anthem on any platform, you’ll need at least the following tools:

* [Git](https://git-scm.com)
* [Python](https://python.org)
  * You should prefer Python 3 over Python 2.7 as the support for Python 2 has ended. However, the build script also works with Python 2.7 to be backwards compatible.
* A C++ compiler toolchain that supports at least C++17
  * **Linux**
    * `make`
    * [LLVM](https://llvm.org) or [GCC](https://gcc.gnu.org)
      * LLVM includes pre-built binaries for some platforms
      * GCC can be installed using your systems package manager
  * **macOS**
    * [Xcode](https://developer.apple.com/xcode) and the Command Line Tools as they will install `clang` and `gcc` and its related toolchain also containing `make`
      * Run `xcode-select --install` to install the Command Line Tools
  * **Windows**
    * Install a compiler by using one of the two options
      1. The first options is to use the Windows Build Tools npm module
        * Start PowerShell as Administrator and install the [Windows Build Tools npm module](https://github.com/felixrieseberg/windows-build-tools)

                npm install --global windows-build-tools

        * This method requires [Node.js](https://nodejs.org)
      2. The second options is to use Visual Studio 2019 Community Edition
        * Install [Visual Studio 2019](https://visualstudio.microsoft.com) Community Edition, which should install all the required tools

## Building

Obliging Ode and Unsung Anthem use their own build script, [Couplet Composer](https://github.com/anttikivi/couplet-composer). Couplet Composer then installs the rest of the tools and dependencies required to build the projects. Couplet Composer is written in Python. Couplet Composer cannot be installed manually as it’s automatically installed by the utility scripts that come with Obliging Ode and Unsung Anthem.

Couplet Composer has two main modes: configuring mode and composing mode. The configuring mode installs the tools and dependencies required to build Obliging Ode and Unsung Anthem using the current configuration and the composing mode only builds Obliging Ode and Unsung Anthem. This process is explained in the platform-specific build instructions below.

### Linux

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        mkdir ode-sources
        cd ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Switch to the cloned directory.

        cd unsung-anthem

4. Set up the build environment by running Couplet Composer in configuring mode.

        ./configure

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./configure preset --name PRESET_NAME

5. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        ./compose

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./compose preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

### macOS

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        mkdir ode-sources
        cd ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Switch to the cloned directory.

        cd unsung-anthem

4. Set up the build environment by running Couplet Composer in configuring mode.

        ./configure

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./configure preset --name PRESET_NAME

5. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        ./compose

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./compose preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

### Windows

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        md ode-sources
        cd ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Switch to the cloned directory.

        cd unsung-anthem

4. Set up the build environment by running Couplet Composer in configuring mode.

        .\configure

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          .\configure preset --name PRESET_NAME

5. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        .\compose

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          .\compose preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

## Configuring the Build

Couplet Composer and the build of Obliging Ode and Unsung Anthem can naturally be configured by using vast selection of command line options. While it is possible to use only traditional command line arguments, the *recommended* way to configure the builds is to use so called **preset mode** of Couplet Composer.

In preset mode, the command line only specifies the preset name. The actual options come from the selected preset in `util/composer-presets.ini`. For example, if you want to run the generic developer build, your configuring mode call looks something like this:

    ./configure preset --name dev

and you composing mode call looks something like this:

    ./compose preset --name dev

On Windows the calls should of course use the Window batch file script variants.

If you take a look into `util/composer-presets.ini`, you can see how the preset is specified in the preset file.

    $ cat > ./util/composer-presets.ini
    ...
    [dev]
    test
    benchmark
    debug
    ninja

    [compose:dev]
    developer-build
    ...

First of all, only so called long names of the options should be used as you can see. Each line below the names of the presets represent one option. If the command line option takes a value, it’s given in the following form: `option=value`.

You must give the options that are common to both configuring and composing mode below the normal name of the preset, in this case `[dev]`. However, some options are exclusive to either configuring or composing mode. You must give those options below the titles that have the name of the mode (either `configure:` or `compose:`) before the name of the preset. In this case, the options of the preset named `dev` that are exclusive to the composing mode are given below the title `[compose:dev]`.

To find out more about the command line options, please read more in the section [Command Line Options](#command-line-options).

You can also your own local files containing presets for Couplet Composer. To add a path to the list of files from which Couplet Composer looks for preset, use the `--file` options.

    ./compose preset --file /path/to/my/file/presets.ini --name some_preset

You can specify the `--file` option multiple times to add more paths to the list of files.

## Command Line Options

### Common Top-level Options

These options can be used in all modes and should be added to presets sparingly. If you use these options as normal command line options when invoking Couplet Composer in preset mode, these will be passed through to the actual invocation of the script even though they’re not specified in the preset.

#### Special Options

**`-h`**, **`--help`**

Shows the help message of Couplet Composer and exits.

**`-v`**, **`--version`**

Shows the version of Couplet Composer and exits.

#### Top-level Options

**`-n`**, **`--dry-run`**

Makes Couplet Composer run so that it only prints the commands that would be run but doesn’t actually run them.

**`-j INTEGER`**, **`--jobs INTEGER`**

Specifies the maximum number of parallel builds jobs Couplet Composer uses.

**`-c`**, **`--clean`**

Cleans the build environment before the build.

**`--print-debug`**

Prints debug-level logging output.

**`--in-tree-build`**

Creates the build directory inside the project directory. **Note:** This option should chiefly be used only on automated environments!

#### GitHub Options

**`--github-auth-file PATH`**

Finds the user agent and API token for accessing the version 4 of the GitHub API from the given file by path relative to the root directory of the project repository (the default path is `util/.github_api`). The first line of the file must contain the user agent and the second the API token.

**`--github-user-agent VALUE`**

Sets the user agent used when accessing the version 4 of the GitHub API. Overrides the value read using the `--github-auth-file` option.

**`--github-api-token TOKEN`**

Sets the API token used when accessing the version 4 of the GitHub API. Overrides the value read using the `--github-auth-file` option.

### Common Options

These options are common to both configuring mode and composing mode but cannot be specified through command line in preset mode.

**`-t`**, **`--test`**

Builds the tests of Obliging Ode and Unsung Anthem.

**`-b`**, **`--benchmark`**

Builds the benchmarks of Obliging Ode and Unsung Anthem with the tests.

**`--docs`**

Builds the documentation of Obliging Ode and Unsung Anthem. This option requires Doxygen, and you must install it manually—Couplet Composer cannot install it for the time being.

**`--lint`**

(Since Couplet Composer 0.13.3)

Runs `clang-tidy` checks on Obliging Ode and Unsung Anthem and prints its output.

**`--ode-version VERSION`**

Sets the version number of Obliging Ode. The default value is the version number specified in `util/values.json`.

**`--anthem-version VERSION`**

Sets the version number of Unsung Anthem. The default value is the version number specified in `util/values.json`.

#### Build Variant Options

You can use only one of the following options.

**`--build-variant {Debug,RelWithDebInfo,Release,MinSizeRel}`**

Sets the build variant to the selected variant. The possible choices are `Debug`, `RelWithDebInfo`, `Release`, and `MinSizeRel`. The default build variant is `Debug`.

**`-d`**, **`--debug`**

Sets the build variant to `Debug`. This option is a shorthand for `--build-variant Debug`.

**`-r`**, **`--release-debuginfo`**

Sets the build variant to `RelWithDebInfo`. This option is a shorthand for `--build-variant RelWithDebInfo`.

**`-R`**, **`--release`**

Sets the build variant to `Release`. This option is a shorthand for `--build-variant Release`.

**`-M`**, **`--minsize-release`**

Sets the build variant to `MinSizeRel`. This option is a shorthand for `--build-variant MinSizeRel`.

#### Build Target Options

Please note that as Couplet Composer is still in development, these options don’t have any effect on the built binaries yet.

**`--host-target TARGET`**

Builds the binaries for the specified host target. The host target is resolved automatically by default.

#### Toolchain Options

In this group, the options `-C`, `--compiler-toolchain`, `--clang`, `--gcc`, and `--msvc` are mutually exclusive.

**`-C {clang,gcc,msvc}`**, **`--compiler-toolchain {clang,gcc,msvc}`**

Resolves the paths to the components of the the given compiler toolchain if no toolchain is given by using `--host-cc` and `--host-cxx` or `--host-compiler`. The possible choices are `clang`, `gcc`, and `msvc`. The default toolchain on Darwin and Linux platforms is `clang` and on Windows platforms `msvc`.

**`--clang`**

Resolves the paths to the components of the the `clang` compiler toolchain if no toolchain is given by using `--host-cc` and `--host-cxx` or `--host-compiler`. This option is a shorthand for `-C clang` or `--compiler-toolchain clang`.

**`--gcc`**

Resolves the paths to the components of the the `gcc` compiler toolchain if no toolchain is given by using `--host-cc` and `--host-cxx` or `--host-compiler`. This option is a shorthand for `-C gcc` or `--compiler-toolchain gcc`.

**`--msvc`**

Resolves the paths to the components of the the `msvc` compiler toolchain if no toolchain is given by using `--host-cc` and `--host-cxx` or `--host-compiler`. This option is a shorthand for `-C msvc` or `--compiler-toolchain msvc`.

**`--compiler-version VERSION`**

Uses the given version number for searching the set compiler toolchain if the compiler toolchain is resolved by the script and not given manually using `--host-cc` and `--host-cxx` or `--host-compiler`.

**`--host-cc EXECUTABLE`**

Specifies the path to the C compiler for the host platform and uses it instead of the automatically resolved C compiler.

**`--host-cxx EXECUTABLE`**

Specifies the path to the C++ compiler for the host platform and uses it instead of the automatically resolved C++ compiler.

**`--host-compiler EXECUTABLE`**

Specifies the path to the compiler for the host platform and uses it instead of the automatically resolved compiler. This option also overrides any value given through `--host-cc` and `--host-cxx`.

**`--host-msbuild EXECUTABLE`**

Specifies the path to MSBuild for the host platform and uses it instead of the automatically resolved MSBuild.

**`--clang-tidy-binary EXECUTABLE`**

(Since Couplet Composer 0.11.0)

Specifies the path to `clang-tidy` for the host platform and uses it instead of the automatically resolved `clang-tidy`.

**`--clang-apply-replacements-binary EXECUTABLE`**

(Since Couplet Composer 0.11.0)

Specifies the path to `clang-apply-replacements` for the host platform and uses it instead of the automatically resolved `clang-apply-replacements`.

#### OpenGL Options

**`--opengl-version`**

Sets the version of OpenGL that Obliging Ode requests from the system.

#### Build Generator Options

You can use only one of the following options.

**`-G {Ninja,Unix Makefiles,Visual Studio 16 2019}`**, **`--cmake-generator {Ninja,Unix Makefiles,Visual Studio 16 2019}`**

Generates the build files using the selected CMake generator. The possible choices are `Ninja`, `Unix Makefiles`, and `Visual Studio 16 2019`. The default build variant is `Ninja`.

**`-N`**, **`--ninja`**

Generates the build files using the `Ninja` CMake generator. This option is a shorthand for `-G Ninja` or `--cmake-generator Ninja`.

**`-m`**, **`--make`**

Generates the build files using the `Unix Makefiles` CMake generator. This option is a shorthand for `-G Unix Makefiles` or `--cmake-generator Unix Makefiles`.

**`--visual-studio-16`**

Generates the build files using the `Visual Studio 16 2019` CMake generator. This option is a shorthand for `-G Visual Studio 16 2019` or `--cmake-generator Visual Studio 16 2019`.

### Preset Mode Options

These options can only be used through command line in preset mode.

**`--file PATH`**

Adds a path to the list of files from which Couplet Composer looks for the presets. You can use this options multiple times to add more paths to the list.

**`--name PRESET`**

Uses the given preset.

**`--show`**

Shows the available presets in the preset files and exits.

**`--expand-script-invocation`**

Prints the build script invocation composed from the preset given using `--name` and exits without running it.

### Configuring Mode Options

These options are only usable in configuring mode.

### Composing Mode Options

These options are only usable in composing mode.

#### Compose: Common Options

**`--ode-static-lib`**

Builds the static library of Obliging Ode.

**`--ode-shared-lib`**

Builds the shared library of Obliging Ode.

**`--anthem-static-lib`**

Builds the static library of Unsung Anthem.

**`--anthem-shared-lib`**

Builds the shared library of Unsung Anthem.

**`--skip-build`**

(Since Couplet Composer 0.13.3)

Only generates the build files for Obliging Ode and Unsung Anthem without compiling them. Especially useful if you want to run linter without compiling the binaries.

**`--export-linter-fixes PATH`**

(Since Couplet Composer 0.11.0)

Exports the fixes suggested by `clang-tidy` to the given file. The path is relative to the source root of the run.

**`--use-artefact-directory`**

(Since Couplet Composer 0.13.0)

Copies the artefact files to a directory instead of archiving them. Especially useful with GitHub Actions.

#### Compose: C++ Standard Options

You can use only one of the following options.

**`--std {c++17,c++20}`**

Compiles Obliging Ode and Unsung Anthem using the given C++ standard. The possible choices are `c++17` and `c++20`. The default standard is `c++17`.

**`--c++17`**

Compiles Obliging Ode and Unsung Anthem using `c++17` as the C++ standard. This option is a shorthand for `--std c++17`.

**`--c++20`**

Compiles Obliging Ode and Unsung Anthem using `c++20` as the C++ standard. This option is a shorthand for `--std c++20`.

#### Compose: Feature Options

**`--ode-window-name NAME`**

Sets the default name of the default window of Obliging Ode.

**`--anthem-window-name NAME`**

Sets the default name of the default window of Unsung Anthem.

**`--ode-logger-name NAME`**

Sets the default name of the default logger of Obliging Ode.

**`--anthem-logger-name NAME`**

Sets the default name of the default logger of Unsung Anthem.

**`--ode-binaries-name NAME`**

Sets the base name of the built binaries of Obliging Ode.

**`--anthem-binaries-name NAME`**

Sets the base name of the built binaries of Unsung Anthem.

**`--anthem-artefacts-name NAME`**

Sets the base name of the artifacts of Unsung Anthem. This option also has an alias, `--anthem-artifacts-name NAME`.

**`-a`, `--assertions`**

Enables assertions in Obliging Ode and Unsung Anthem. Assertions are enabled by default.

**`-A`, `--no-assertions`**

Disables assertions in Obliging Ode and Unsung Anthem. Assertions are enabled by default.

**`-D`, `--developer-build`**

Enables developer features in the built binaries of Obliging Ode and Unsung Anthem.

**`--test-logging`**

Enables writing of the logger output in the tests if the tests are built.

## Environment Variables

In addition to the command line options, Couplet Composer and the utility scripts can be configured by a couple of environment variables. The environment variables are not for standard everyday use but rather for miscellaneous debugging and testing.

**`ODE_DEVELOPMENT_COMPOSER`**

If `ODE_DEVELOPMENT_COMPOSER` is set to `true`, the utility script uses the latest development version of Couplet Composer instead of the release version it normally would.
