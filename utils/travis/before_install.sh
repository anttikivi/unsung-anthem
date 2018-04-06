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

if [ "${TRAVIS_OS_NAME}" == "osx" ] \
    && [ "${TRAVIS_OSX_IMAGE}" == "xcode6.4" ]; then
  # export PATH=$PATH:~/Library/Python/2.7/bin
  # brew update
  brew install python
fi

if [ "${TRAVIS_OSX_IMAGE}" == "xcode7.3" ] \
    || [ "${TRAVIS_OSX_IMAGE}" == "xcode8.3" ] \
    || [ "${TRAVIS_OSX_IMAGE}" == "xcode9.3beta" ]; then
  echo Using python2 and pip2 instead of pip
elif [ "${TRAVIS_OSX_IMAGE}" == "xcode6.4" ]; then
  echo Using python3 and pip3 instead of pip
fi

if [ "${TRAVIS_OSX_IMAGE}" == "xcode7.3" ] \
    || [ "${TRAVIS_OSX_IMAGE}" == "xcode8.3" ] \
    || [ "${TRAVIS_OSX_IMAGE}" == "xcode9.3beta" ]; then
  pip2 install --user request
elif [ "${TRAVIS_OSX_IMAGE}" == "xcode6.4" ]; then
  pip3 install --user request
else
  pip install --user request
fi

if [ "${ENABLE_COVERAGE}" == "true" ]; then
  gem install coveralls-lcov
fi
