# Building Obliging Ode and Unsung Anthem

Whether you want to contribute to Obliging Ode and Unsung Anthem or simply try out the latest and greatest features of the projects, you need to build the projects from source. Luckily it’s quite simple. The building process for each officially supported platform is explained in this document.

## Table of Contents

* [Prerequisites](#prerequisites)
* [Building](#building)
  * [Linux](#linux)
  * [macOS](#macos)
  * [Windows](#windows)
    * [Using Command Prompt](#using-command-prompt)
    * [Using PowerShell](#using-powershell)
* [Configuring the Build](#configuring-the-build)
* [Command Line Options](#command-line-options)
  * [Common Top-level Options](#common-top-level-options)
  * [Common Options](#common-options)

## Prerequisites

To build Obliging Ode and Unsung Anthem on any platform, you’ll need at least the following tools:

* [Git](https://git-scm.com)
* [Python](https://python.org)
  * You should prefer Python 3 over Python 2.7 as the support for Python 2 has ended. However, the build script also works with Python 2.7 for compatibility reasons.
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

3. Set up the build environment by running Couplet Composer in configuring mode.

        ./unsung-anthem/util/configure

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./unsung-anthem/util/configure preset --name PRESET_NAME

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        ./unsung-anthem/util/compose

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./unsung-anthem/util/compose preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

### macOS

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        mkdir ode-sources
        cd ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Set up the build environment by running Couplet Composer in configuring mode.

        ./unsung-anthem/util/configure

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./unsung-anthem/util/configure preset --name PRESET_NAME

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        ./unsung-anthem/util/compose

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          ./unsung-anthem/util/compose preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

### Windows

You can run the commands on Windows by using either [Command Prompt](#using-command-prompt) or [PowerShell](#using-powershell). Below you can find instructions for both.

#### Using Command Prompt

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        mkdir ode-sources
        cd ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Set up the build environment by running Couplet Composer in configuring mode.

        .\unsung-anthem\util\configure.ps1

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          .\unsung-anthem\util\configure.ps1 preset --name PRESET_NAME

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        .\unsung-anthem\util\compose.ps1

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          .\unsung-anthem\util\compose.ps1 preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

#### Using PowerShell

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        New-Item ode-sources -ItemType directory
        Set-Location ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Set up the build environment by running Couplet Composer in configuring mode.

        .\unsung-anthem\util\configure.ps1

  * To invoke the configuring mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          .\unsung-anthem\util\configure.ps1 preset --name PRESET_NAME

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        .\unsung-anthem\util\compose.ps1

  * To invoke the composing mode of Couplet Composer through an option preset, use the following command where `PRESET_NAME` is the name of the option preset you want to use. For more information, see the section [Configuring the Build](#configuring-the-build).

          .\unsung-anthem\util\compose.ps1 preset --name PRESET_NAME

**Note:** The build can be configured by using option presets and command line options. For more information, see the section [Configuring the Build](#configuring-the-build).

## Configuring the Build

Couplet Composer and the build of Obliging Ode and Unsung Anthem can naturally be configured by using vast selection of command line options. While it is possible to use only traditional command line arguments, the *recommended* way to configure the builds is to use so called **preset mode** of Couplet Composer.

In preset mode, the command line only specifies the preset name. The actual options come from the selected preset in `util/composer-presets.ini`. For example, if you want to run the generic developer build, your configuring mode call looks something like this:

    ./unsung-anthem/util/configure preset --name dev

and you composing mode call looks something like this:

    ./unsung-anthem/util/compose preset --name dev

On Windows the calls should of course use the PowerShell script variants.

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

    ./unsung-anthem/util/compose preset --file /path/to/my/file/presets.ini --name some_preset

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

**`--ode-version VERSION`**

Sets the version number of Obliging Ode. The default value is the version number specified in `util/values.json`.

**`--anthem-version VERSION`**

Sets the version number of Unsung Anthem. The default value is the version number specified in `util/values.json`.

#### Build Variant Options

You can use only one of the following options.

**`--build-variant {Debug,RelWithDebInfo,Release,MinSizeRel}`**

Sets the build variant to the selected variant. The possible choices are `Debug`, `RelWithDebInfo`, `Release`, and `MinSizeRel`. The default build variant is `Debug`.

**`-d`**, **`--debug`**

Sets the build variant to `Debug`.

**`-r`**, **`--release-debuginfo`**

Sets the build variant to `RelWithDebInfo`.

**`-R`**, **`--release`**

Sets the build variant to `Release`.

**`-M`**, **`--minsize-release`**

Sets the build variant to `MinSizeRel`.
