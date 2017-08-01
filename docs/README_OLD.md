insert a logo here

# Unsung Anthem

[![Build Status](https://travis-ci.org/venturesomestone/unsung-anthem.svg?branch=develop)](https://travis-ci.org/venturesomestone/unsung-anthem) [![CircleCI](https://circleci.com/gh/venturesomestone/unsung-anthem/tree/develop.svg?style=svg)](https://circleci.com/gh/venturesomestone/unsung-anthem/tree/develop) [![Build status](https://ci.appveyor.com/api/projects/status/h387p7t5hw89s8ty/branch/develop?svg=true)](https://ci.appveyor.com/project/venturesomestone/unsung-anthem/branch/develop) [![Coverage Status](https://coveralls.io/repos/github/venturesomestone/unsung-anthem/badge.svg?branch=develop)](https://coveralls.io/github/venturesomestone/unsung-anthem?branch=develop)

**Welcome to Unsung Anthem!**

This README is not ready yet!

Unsung Anthem is a 2D video game with own game engine. It is written by using modern C++ and functional programming paradigm.


## Documentation

To read the documentation, start by installing the TeX and LaTeX tools for your system.

* [macOS](#macOS)
* [Debian-based systems (for example, Ubuntu)](#Debian)

Once complete, you can build the Unsung Anthem documentation by running the build script with documentation enabled

    ./unsung-anthem/utils/build-script --build-docs

Alternatively, you can build the documentation by running the build script with only documentation build enabled

    ./unsung-anthem/utils/build-script --docs

Finally, the last alternative for building the documentation is to change directory into [docs/sources](https://github.com/venturesomestone/unsung-anthem/tree/develop/docs/sources) (`cd ./unsung-anthem/docs/sources`) and typing the command

    latexmk -pdf anthem

This compiles the `.tex` files in the [docs/sources](https://github.com/venturesomestone/unsung-anthem/tree/develop/docs/sources) directory into a PDF in the `docs/sources` directory.


### macOS

Install the [MacTeX distribution](http://tug.org/mactex).

If you are on a slow network, you'll want to get the [BasicTeX package](http://tug.org/mactex/morepackages.html) instead, and after that run the following command to install the other packages that the documentation requires:

    sudo tlmgr install latexmk isodate substr relsize ulem fixme rsfs extract layouts enumitem


### Debian

Install the following packages:

    sudo apt-get install latexmk texlive-latex-recommended texlive-latex-extra texlive-fonts-recommended


## Getting Started

These instructions give the most direct path to a working Unsung Anthem development environment. Options for doing things differently are discussed below.


### System Requirements

macOS, Ubuntu Linux LTS, and Microsoft Windows release are the current, officially supported host development operating systems.

For macOS, you need [Xcode](https://developer.apple.com/xcode/downloads/).

<a name="linux-dependencies"></a>For Ubuntu, you'll need the following development dependencies:

    sudo apt-get install git clang python libpython-dev pkg-config autoconf xorg-dev libglu1-mesa-dev build-essential libc++-dev


### Getting Sources for Unsung Anthem and Related Projects

First create a directory for all of the Unsung Anthem sources:

    mkdir anthem-source
    cd anthem-source

**Note:** This is important since checkout update (see below) checks out repositories next to the Unsung Anthem source directory. This means that if one clones Unsung Anthem and has other unrelated repositories, checkout update may not clone those repositories.

**Via HTTPS**  For those checking out sources as read-only, HTTPS works best:

    git clone https://github.com/venturesomestone/unsung-anthem.git

**Via SSH**  For those who plan on regularly making direct commits, cloning over SSH may provide a better experience (which requires [uploading SSH keys to GitHub](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/)):

    git clone git@github.com:venturesomestone/unsung-anthem.git

After cloning Unsung Anthem, the build script will download the sources and binaries for the dependencies automatically. If you want to, for some reason, download them beforehand, run

    ./unsung-anthem/utils/build-script --update-checkout


#### CMake
[CMake](https://cmake.org) is the core infrastructure used to configure builds of Unsung Anthem and its companion projects; at least version 2.8.12 is required.

The build script will download CMake automatically if you choose to not install it by yourself.

On macOS, you can download the [CMake Binary Distribution](https://cmake.org/download), bundled as an application, copy it to `/Applications`, and add the embedded command line tools to your `PATH`:

    export PATH=/Applications/CMake.app/Contents/bin:$PATH

On Linux, if you have not already installed the [development dependencies](#linux-dependencies) if Unsung Anthem, you can download and install the CMake package separately using the following command:

    sudo apt-get install cmake


#### Ninja
[Ninja](https://ninja-build.org) is the current recommended build system for building Unsung Anthem and is the default configuration generated by CMake. [Pre-built packages](https://github.com/ninja-build/ninja/wiki/Pre-built-Ninja-packages) are available for macOS and Linux distributions. Also, the build script will download Ninja automatically if it is not found on the system.


#### Install via third-party packaging tool (macOS only)

**[Homebrew](https://brew.sh/)**

    brew install cmake ninja

**[MacPorts](https://macports.org)**

    sudo port install cmake ninja


### Building Unsung Anthem

The `build-script` is a high-level build automation script that supports basic options such as running tests after builds and more. It also supports presets, which you can define for common combinations of build options.

To find out more:

    unsung-anthem/utils/build-script -h

A basic command to build Unsung Anthem with optimizations and run basic tests with Ninja:

    unsung-anthem/utils/build-script -R -t


## Developing Unsung Anthem in Xcode

`build-script` can also generate Xcode projects:

    utils/build-script -x

The Xcode IDE can be used to edit the Unsung Anthem source code.


## Developing Unsung Anthem in JetBrains CLion

`build-script` can output CMake arguments to be set into CLion:

    utils/build-script --clion


## Testing Unsung Anthem

TODO


## Contributing to Unsung Anthem

Contributions to Unsung Anthem are welcomed and encouraged! Please see the [Contributing to Unsung Anthem guide (TODO)](#).

To be a truly great community, [Unsung Anthem (TODO)](#) needs to welcome developers from all walks of life, with different backgrounds, and with a wide range of experience. A diverse and friendly community will have more great ideas, more unique perspectives, and produce more great code. We will work diligently to make the Unsung Anthem community welcoming to everyone.

To give clarity of what is expected of our members, Unsung Anthem has adopted the code of conduct defined by the Citizen Code of Conduct. This document is used across many open source communities, and we think it articulates our values well. For more, see the [Code of Conduct](https://github.com/venturesomestone/unsung-anthem/blob/develop/CODE_OF_CONDUCT.md).


## Values and Principles

The goal of Unsung Anthem is to be a game that embraces different styles of play and preferences of people. This will be strengthened by the storytelling of Unsung Anthem:

* Unsung Anthem is an open-air game.
* It can still be progressed somewhat linearly if the player wants to follow thin story.
* Player can discover a deeper story and lore hidden in the world, items, and dialogues of Unsung Anthem if they want to so the storytelling of Unsung Anthem resembles that of Dark Souls.

Unsung Anthem is supposed to be difficult and challenging but not punishing. Whenever the player does not overcome some challenge, they will not consistently blame the failure on Unsung Anthem but rather think how they could succeed by improving themselves.

The difficulty of Unsung Anthem will not be scalable by game settings. It will instead change according to player's decisions. For example, long-range combat could feel easier in some situations so the player chooses it instead of close-range combat. Still, Unsung Anthem maintains its combat system in such manner that players who choose to use more demanding styles of play will feel rewarded once they master the skill.

Also, one in-game solution, for example long-range combat, must not be viable in easing the player in every situation. The player has to find new and dissimilar strategies in different circumstances. The player will feel themselves clever for discovering these novel manoeuvres.

Unsung Anthem encourages the player to venture and look actively for new things to discover. The player will usually be rewarded for undertaking something risky and trying to uncover some secrets.

While Unsung Anthem is supposed to be challenging, writing it should not be. The code of Unsung Anthem follows clear and consistent rules for easier understanding of code. The code must always be well documented.
