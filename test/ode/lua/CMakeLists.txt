#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/script_test.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/state_test.cpp)

set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)
set(ODE_TEST_INCLUDES ${ODE_TEST_INCLUDES} PARENT_SCOPE)
