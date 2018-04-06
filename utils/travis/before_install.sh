#!/bin/bash

#===-------------------------- before_install.sh ---------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

set -v

if [ "${TRAVIS_OS_NAME}" == "osx" ]; then
  # export PATH=$PATH:~/Library/Python/2.7/bin
  brew update
  brew install python
fi

${CC} --version
${CXX} --version
which python
which python2
which python3
which pip
which pip2
which pip3
