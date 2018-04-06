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
  export PATH=~/Library/Python/2.7/bin:$PATH
fi

${ODE_PYTHON:-python} unsung-anthem/utils/build-script --develop-script
