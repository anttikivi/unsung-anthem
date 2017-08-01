insert a logo here

# Unsung Anthem

[![Build Status](https://travis-ci.org/venturesomestone/unsung-anthem.svg?branch=develop)](https://travis-ci.org/venturesomestone/unsung-anthem)[![CircleCI](https://circleci.com/gh/venturesomestone/unsung-anthem/tree/develop.svg?style=svg)](https://circleci.com/gh/venturesomestone/unsung-anthem/tree/develop)[![Build status](https://ci.appveyor.com/api/projects/status/h387p7t5hw89s8ty/branch/develop?svg=true)](https://ci.appveyor.com/project/venturesomestone/unsung-anthem/branch/develop)[![Coverage Status](https://coveralls.io/repos/github/venturesomestone/unsung-anthem/badge.svg?branch=develop)](https://coveralls.io/github/venturesomestone/unsung-anthem?branch=develop)

**Welcome to Unsung Anthem!**

This README is not ready yet!

Unsung Anthem is a 2D video game with own game engine. It is written by using modern C++ and functional programming paradigm as far as modern C++ allows.

## Getting Started

These instructions give the most direct path to setting up a working Unsung Anthem environment for building, testing, and development. Options for doing things differently are discussed below.

### System Requirements

The current, officially supported systems for building and developing Unsung Anthem are

* somewhat recent macOS,
* Ubuntu Linux (preferably 12.02 or later), and
* Microsoft Windows (preferably 8 or later).

Other systems might and most probably will work for building when properly set up.

### Prerequisites

For the minimal manual set up, a C++ compiler and [Python](https://www.python.org) is required. Python 3 should be preferred to Python 2, but both Python 2 and 3 are currently supported. This may, however, change in the future as [the end of life of Python 2 is announced](https://www.python.org/dev/peps/pep-0373/).

[Clang](https://clang.llvm.org) is the recommended C++ compiler to use. Pre-built Clang binaries can be downloaded from [the LLVM website](http://releases.llvm.org). Other, platform-specific ways of installing the compiler are discussed more below.

The current, officially supported compilers include

* Clang (3.5 or greater),
* GCC (5.0 or greater), and
* Visual C++ (14.0 or greater).

#### macOS

On macOS, the easiest way to set up the prerequisites is to download and install [Xcode](https://developer.apple.com/xcode/).

#### Linux

On Ubuntu Linux, the minimum prerequisites can be set up by running the following command:

    sudo apt-get install git clang python build-essential xorg-dev libglu1-mesa-dev

In addition to these packages, `cmake` and `ninja-build` can be installed. However, if they are not installed manually, the build script will download them.

### Building Unsung Anthem

First, create a directory for the Unsung Anthem sources and switch to it

    mkdir anthem-sources
    cd anthem-sources

**Note:** This is important since the build script checks out repositories next to the Unsung Anthem source directory. This means that if one clones Unsung Anthem and has other unrelated repositories next to it, the build script could fail or modify the repositories.

Then clone the Unsung Anthem GitHub repository.

**Via HTTPS:** For those checking out sources as read-only, HTTPS works best

    git clone https://github.com/venturesomestone/unsung-anthem.git

**Via SSH:** For those who plan on regularly making direct commits, cloning over SSH may provide a better experience (which requires [uploading SSH keys to GitHub](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/))

    git clone git@github.com:venturesomestone/unsung-anthem.git

After cloning the source, run the following commands.

*macOS and Linux:*

    chmod +x ./unsung-anthem/utils/build-script
    ./unsung-anthem/utils/build-script

*Windows:*

    python unsung-anthem\utils\build-script

For more detailed information about building Unsung Anthem, see [BUILDING.md](https://github.com/venturesomestone/unsung-anthem/blob/develop/BUILDING.md) (it does not exists yet).

### Developing Unsung Anthem

The build script can be used to set up development environment of Unsung Anthem. Currently the build script supports Xcode and CLion.

**Xcode:** To set up Xcode environment, run the following command

    ./unsung-anthem/utils/build-script -x

**CLion:** To set up CLion environment, run the following command

    ./unsung-anthem/utils/build-script --clion

The command will output list a CMake call from which the options can be copied to CLion.

### Running the Tests

The build script will automatically build and run tests when `-t` option is used. For more information, see [BUILDING.md](https://github.com/venturesomestone/unsung-anthem/blob/develop/BUILDING.md).

## Contributing to Unsung Anthem

Contributions to Unsung Anthem are welcomed and encouraged! Please see the [Contributing to Unsung Anthem guide](https://github.com/venturesomestone/unsung-anthem/blob/develop/CONTRIBUTING.md).

To be a truly great community, [Unsung Anthem](https://github.com/venturesomestone/unsung-anthem/) needs to welcome developers from all walks of life, with different backgrounds, and with a wide range of experience. A diverse and friendly community will have more great ideas, more unique perspectives, and produce more great code. We will work diligently to make the Unsung Anthem community welcoming to everyone.

To give clarity of what is expected of our members, Unsung Anthem has adopted the code of conduct defined by the Contributor Covenant. This document is used across many open source communities, and we think it articulates our values well. For more, see the [Code of Conduct](https://github.com/venturesomestone/unsung-anthem/blob/develop/CODE_OF_CONDUCT.md).
