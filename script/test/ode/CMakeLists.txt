#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/script.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/stack.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/state.lua)
list(APPEND ODE_TEST_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine.lua)
list(APPEND ODE_TEST_SCRIPTS
    ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine_benchmark.lua)

set(ODE_TEST_SCRIPTS ${ODE_TEST_SCRIPTS} PARENT_SCOPE)
