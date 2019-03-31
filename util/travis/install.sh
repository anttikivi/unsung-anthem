#!/bin/bash

#===------------------------------ install.sh ------------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

set -ev

${ODE_PYTHON:-python} unsung-anthem/utils/build-script --develop-script -v
