#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(common)
add_subdirectory(gl)
add_subdirectory(lua)
add_subdirectory(sdl)

list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/logger_test.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/logging_set_up.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/logging_test.cpp)
list(APPEND ODE_TEST_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)

list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/logger_benchmark.cpp)
list(APPEND ODE_BENCHMARK_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/logging_benchmark.cpp)

list(APPEND ODE_TEST_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logging_set_up.h)

set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)
set(ODE_BENCHMARK_SOURCES ${ODE_BENCHMARK_SOURCES} PARENT_SCOPE)
set(ODE_TEST_INCLUDES ${ODE_TEST_INCLUDES} PARENT_SCOPE)
