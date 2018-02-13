insert a logo here

# Unsung Anthem

[![Build Status](https://travis-ci.org/venturesomestone/unsung-anthem.svg?branch=develop)](https://travis-ci.org/venturesomestone/unsung-anthem) [![CircleCI](https://circleci.com/gh/venturesomestone/unsung-anthem/tree/develop.svg?style=svg)](https://circleci.com/gh/venturesomestone/unsung-anthem/tree/develop) [![Build status](https://ci.appveyor.com/api/projects/status/h387p7t5hw89s8ty/branch/develop?svg=true)](https://ci.appveyor.com/project/venturesomestone/unsung-anthem/branch/develop) [![Coverage Status](https://coveralls.io/repos/github/venturesomestone/unsung-anthem/badge.svg?branch=develop)](https://coveralls.io/github/venturesomestone/unsung-anthem?branch=develop)

This README isn’t ready yet!

Unsung Anthem is a video game with its own game engine, ‘Obliging Ode’.

This project adheres to the Contributor Covenant [code of conduct](CODE_OF_CONDUCT.md). By participating, you’re expected to uphold this code. Please report unacceptable behaviour to venturesomestone@gmail.com.

## Installing

There are no pre-built binaries available yet. You can find the instructions on building Unsung Anthem down below.

### Prerequisites

* C and C++ compilers with support for the C++14 standard
  * [Clang](https://clang.llvm.org) is the recommended compiler. You can download the pre-built Clang binaries from [the LLVM website](http://releases.llvm.org)
* [Python](https://www.python.org)
  * Both Python 2 and 3 are currently supported. However, this may change in the future as [the end of life of Python 2 is announced](https://www.python.org/dev/peps/pep-0373/)
    * [Python 2.7 Countdown](https://pythonclock.org)
* [Git](https://git-scm.com)

### Building

These are the basic instructions on building Obliging Ode Unsung Anthem. For more detailed platform-specific guide, please see the following instructions:
* [Linux](./docs/build-instructions/linux.md)
* [macOS](./docs/build-instructions/macos.md)
* [Windows](./docs/build-instructions/windows.md)

First, create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

    mkdir anthem-sources
    cd anthem-sources

**Note:** This is important because the build script checks out repositories next to the Obliging Ode and Unsung Anthem source directory. This means that if you clone Unsung Anthem and have some other unrelated repositories next to it, the build script could fail or modify the repositories.

Then clone the Obliging Ode and Unsung Anthem GitHub repository.

**Via HTTPS:** If you’re checking out sources as read-only, HTTPS works best.

    git clone https://github.com/venturesomestone/unsung-anthem.git

**Via SSH:** If you’re planning on regularly making direct commits, cloning over SSH may provide a better experience (it requires [uploading SSH keys to GitHub](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/))

    git clone git@github.com:venturesomestone/unsung-anthem.git

After cloning the source, run the build script.

    ./unsung-anthem/utils/build-script


## Contributing to Unsung Anthem

Contributions to Obliging Ode and Unsung Anthem are welcome and encouraged! Please see the [Contributing to Unsung Anthem guide](https://github.com/venturesomestone/unsung-anthem/blob/develop/CONTRIBUTING.md).
