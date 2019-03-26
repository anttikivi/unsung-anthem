#!/bin/bash

#===---------------------------- after_script.sh ---------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

set -ev

find . -type f \( -name "*.txt" -o -name "*.yml" -o -name "*.cmake" -o -name "*.h" -o -name "*.cpp" -o -name "assert" -o -name "util" -o -name "view" -o -name "__config" -o -name "*.lua" -o -name "*.ini" -o -name "*.py" -o -name "build-script" -o -name "clean-script" -o -name "*.sh" \) -exec sed -i "" -e "s/All rights reserved/All rights reserved/g" {} +
