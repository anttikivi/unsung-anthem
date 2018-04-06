#!/bin/bash

#===------------------------------ script.sh -------------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

set -ev

if [ "${TRAVIS_OSX_IMAGE}" == "xcode7.3" ] \
    || [ "${TRAVIS_OSX_IMAGE}" == "xcode8.3" ] \
    || [ "${TRAVIS_OSX_IMAGE}" == "xcode9.3beta" ]; then
  python2 script/build-script --preset ${BUILD_PRESET}
elif [ "${TRAVIS_OSX_IMAGE}" == "xcode6.4" ]; then
  python3 script/build-script --preset ${BUILD_PRESET}
else
  python script/build-script --preset ${BUILD_PRESET}
fi
