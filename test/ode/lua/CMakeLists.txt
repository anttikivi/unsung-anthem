#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/script_test.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/stack_test.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/state_test.cpp)
list(APPEND ODE_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine_test.cpp)

list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/script_benchmark.cpp)
list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/stack_benchmark.cpp)
list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/state_benchmark.cpp)
list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine_benchmark.cpp)

set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)
set(ODE_BENCHMARK_SOURCES ${ODE_BENCHMARK_SOURCES} PARENT_SCOPE)
set(ODE_TEST_INCLUDES ${ODE_TEST_INCLUDES} PARENT_SCOPE)
