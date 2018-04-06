#!/bin/bash

#===------------------------------ install.sh ------------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

set -ev

if [ "${TRAVIS_OS_NAME}" == "osx" ]; then
  export PATH=$PATH:~/Library/Python/2.7/bin
fi

# if [ "${TRAVIS_OSX_IMAGE}" == "xcode7.3" ] \
#     || [ "${TRAVIS_OSX_IMAGE}" == "xcode8.3" ] \
#     || [ "${TRAVIS_OSX_IMAGE}" == "xcode9.3beta" ]; then
#   python2 unsung-anthem/utils/build-script --develop-script
# elif [ "${TRAVIS_OSX_IMAGE}" == "xcode6.4" ]; then
#   python3 unsung-anthem/utils/build-script --develop-script
# else
#   python unsung-anthem/utils/build-script --develop-script
# fi

python unsung-anthem/utils/build-script --develop-script
