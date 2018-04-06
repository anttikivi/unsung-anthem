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

${CC} --version
${CXX} --version

if [ "${TRAVIS_OS_NAME}" == "osx" ]; then
  export PATH=~/Library/Python/2.7/bin:$PATH
fi

which pip2
pip2 install --user request

if [ "${ENABLE_COVERAGE}" == "true" ]; then
  gem install coveralls-lcov
fi
