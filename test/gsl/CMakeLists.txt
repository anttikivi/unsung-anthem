#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved

list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/util_test.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/view_test.cpp)

set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)
