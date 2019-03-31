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

cloc assets cmake docs include lib script src test utils ../script
