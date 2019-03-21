#!/bin/bash

#===-------------------------- before_install.sh ---------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# Licensed under GNU Affero General Public License v3.0

set -ev

if [ "${TRAVIS_OSX_IMAGE}" == "xcode6.4" ]; then
  brew update
  brew install python
fi

${ODE_PIP:-pip} install --user requests

npm install -g cloc

if [ "${ENABLE_COVERAGE}" == "true" ]; then
  gem install coveralls-lcov
fi

if [ "${TRAVIS_OS_NAME}" == "osx" ]; then
  mkdir clang-temp
  cd clang-temp
  curl -O http://releases.llvm.org/6.0.0/clang+llvm-6.0.0-x86_64-apple-darwin.tar.xz
  tar -xf clang+llvm-6.0.0-x86_64-apple-darwin.tar.xz
  cd clang+llvm-6.0.0-x86_64-apple-darwin
  yes | cp -Rf bin/ /usr/local/bin
  yes | cp -Rf include/ /usr/local/include
  yes | cp -Rf lib/ /usr/local/lib
  yes | cp -Rf share/ /usr/local/share
  cd ..
  cd ..
  rm -Rf clang-temp
  /usr/local/bin/clang --version
  /usr/local/bin/clang++ --version
fi
