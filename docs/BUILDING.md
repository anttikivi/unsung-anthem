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
      1. Use the Windows Build Tools npm module
        * Start PowerShell as Administrator and the [Windows Build Tools npm module](https://github.com/felixrieseberg/windows-build-tools)

                npm install --global windows-build-tools

        * This method requires [Node.js](https://nodejs.org)
      2. Use Visual Studio 2019 Community Edition
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

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        ./unsung-anthem/util/compose

### macOS

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        mkdir ode-sources
        cd ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Set up the build environment by running Couplet Composer in configuring mode.

        ./unsung-anthem/util/configure

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        ./unsung-anthem/util/compose

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

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        .\unsung-anthem\util\compose.ps1

#### Using PowerShell

1. Create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

        New-Item ode-sources -ItemType directory
        Set-Location ode-sources

    **Note:** This is important because Couplet Composer and the utility scripts check out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories or other directories next to it, the build script could fail or modify the repositories.

2. Clone the GitHub repository of Obliging Ode and Unsung Anthem.

        git clone https://github.com/anttikivi/unsung-anthem.git

3. Set up the build environment by running Couplet Composer in configuring mode.

        .\unsung-anthem\util\configure.ps1

4. Build Obliging Ode and Unsung Anthem by running Couplet Composer in composing mode.

        .\unsung-anthem\util\compose.ps1
