#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/script.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/stack.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/stack_push.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/state.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine.lua)
list(APPEND ODE_TEST_SCRIPTS
    ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine_benchmark.lua)

set(ODE_TEST_SCRIPTS ${ODE_TEST_SCRIPTS} PARENT_SCOPE)
