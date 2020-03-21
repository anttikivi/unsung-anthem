# Unsung Anthem
**with Obliging Ode**

![](https://github.com/anttikivi/unsung-anthem/workflows/Main%20workflow/badge.svg) [![Coverage Status](https://coveralls.io/repos/github/anttikivi/unsung-anthem/badge.svg?branch=develop)](https://coveralls.io/github/anttikivi/unsung-anthem?branch=develop)

*Unsung Anthem* is a video game with its own game engine, *Obliging Ode*. The development of the project is still in very early stage. This repository contains the source code for both Unsung Anthem and Obliging Ode.

The guidelines and other documentation hosted in this repository are also applied to other projects that support Unsung Anthem and Obliging Ode. Those projects include the build script and the licence of Unsung Anthem and Obliging Ode. All of the projects and their Git repositories are:

* Unsung Anthem ([unsung-anthem](https://github.com/anttikivi/unsung-anthem))
* Obliging Ode ([unsung-anthem](https://github.com/anttikivi/unsung-anthem))
* Couplet Composer ([couplet-composer](https://github.com/anttikivi/couplet-composer))
* Effective Elegy ([effective-elegy](https://github.com/anttikivi/effective-elegy))

## Installing

There are no pre-built binaries available yet. To use Unsung Anthem, please follow the building instructions down below.

## Contribute

Contributions to Obliging Ode and Unsung Anthem are welcome and encouraged! There are many ways to [contribute](CONTRIBUTING.md) to Obliging Ode and Unsung Anthem.

This project adheres to the Contributor Covenant [Code of Conduct](CODE_OF_CONDUCT.md). By participating, you’re expected to uphold this code. Please report unacceptable behaviour to antti.kivi@visiosto.fi.

## Building

Please ensure you have a C++17 compliant compiler, [Git](https://git-scm.com), and [Python](https://python.org).

For more complete and platform-specific instructions, please see the [building instructions](docs/BUILDING.md).

First, create a directory for the Obliging Ode and Unsung Anthem sources and switch to it.

    mkdir anthem-sources
    cd anthem-sources

**Note:** This is important because the build script checks out repositories next to the source directory of Obliging Ode and Unsung Anthem. This means that if you clone Obliging Ode and Unsung Anthem and have some other unrelated repositories next to it, the build script could fail or modify the repositories.

Then clone the GitHub repository of Obliging Ode and Unsung Anthem.

**Via HTTPS:** If you’re checking out sources as read-only, HTTPS works best.

    git clone https://github.com/anttikivi/unsung-anthem.git

**Via SSH:** If you’re planning on regularly making direct commits, cloning over SSH may provide a better experience (it requires [uploading SSH keys to GitHub](https://help.github.com/articles/adding-a-new-ssh-key-to-your-github-account/))

    git clone git@github.com:anttikivi/unsung-anthem.git

After cloning the source, run the configuring script to set up the build environment.

    ./unsung-anthem/util/configure

When the configuring script has finished, run the build script.

    ./unsung-anthem/util/compose


## Roadmap

For details on our planned features and future direction please refer to the [roadmap (not available yet)](https://github.com/anttikivi/unsung-anthem) project.
