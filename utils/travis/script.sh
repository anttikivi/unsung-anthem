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

if [ "${ENABLE_COVERAGE}" == "true" ]; then
  cd /
fi

${ODE_PYTHON:-python} script/build-script --preset ${BUILD_PRESET} -v
