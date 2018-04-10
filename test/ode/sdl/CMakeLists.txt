#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/version_test.cpp)

list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/version_benchmark.cpp)

set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)
set(ODE_BENCHMARK_SOURCES ${ODE_BENCHMARK_SOURCES} PARENT_SCOPE)
