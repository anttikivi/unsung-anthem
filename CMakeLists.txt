#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

cmake_minimum_required(VERSION 2.8.12)
project(anthem)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

include(CompilerFlags)
include(Definitions)
include(ExternalSources)
include(Install)
include(StdDefinitions)
include(Targets)
include(Variables)

option(BUILD_ODE "Build Obliging Ode" OFF)

option(ODE_ENABLE_GCOV "Add target for gcov code coverage" OFF)

option(ODE_ENABLE_ASSERTIONS
    "Option for enabling assertions in Obliging Ode" ON)

option(ANTHEM_ENABLE_ASSERTIONS
    "Option for enabling assertions in Unsung Anthem" ON)

option(ODE_DEVELOPER "Enable developer mode in Obliging Ode" OFF)

option(ANTHEM_DEVELOPER "Enable developer mode in Unsung Anthem" OFF)

option(ODE_TEST_BENCHMARKING "Build the benchmarkings in Obliging Ode" OFF)

option(ANTHEM_TEST_BENCHMARKING "Build the benchmarkings in Unsung Anthem" OFF)

option(ODE_MULTITHREADING "Enable multithreading in the product" ON)

option(ODE_MANUAL_SDL "Simple DirectMedia Layer is linked manually" OFF)

option(ODE_SET_RPATH "Set the rpath to the install directory" OFF)

option(ODE_LINK_LIBCXX "Manually link libc++" OFF)

option(ODE_ADD_LUA_SOURCE
    "Add Lua source files directly to the Ode sources" OFF)

option(ODE_INSTALL_ONLY_SCRIPTS "Install only the scripts" OFF)

if(BUILD_ODE)
  assert_variable(ODE_TYPE "Obliging Ode product type" "lib and test")
else()
  assert_variable(ANTHEM_TYPE "Unsung Anthem product type" "exe, lib, and test")
endif()

assert_variable(ODE_CXX_VERSION "C++ standard version" "c++2a and c++17")

assert_variable(ODE_INSTALL_PREFIX "dependency installation directory")

assert_variable(ODE_BIN_DIR_NAME "name of the binary installation directory")
assert_variable(ODE_INCLUDE_DIR_NAME
    "name of the include installation directory")
assert_variable(ODE_LIB_DIR_NAME "name of the library installation directory")
assert_variable(ODE_SCRIPT_DIR_NAME 
    "name of the script installation directory")

set(ODE_LIB_SCRIPT_DIR_NAME "${ODE_SCRIPT_DIR_NAME}/lib")
set(ODE_TEST_SCRIPT_DIR_NAME "${ODE_SCRIPT_DIR_NAME}/test")

print_status(ODE_LIB_SCRIPT_DIR_NAME "library script installation directory")
print_status(ODE_TEST_SCRIPT_DIR_NAME "test script installation directory")

assert_variable(ODE_OPENGL_VERSION_MAJOR "OpenGL major version")
assert_variable(ODE_OPENGL_VERSION_MINOR "OpenGL minor version")

assert_variable(ODE_LOGGER_NAME "engine logger name")
assert_variable(ODE_WINDOW_NAME "engine window name")

if(NOT BUILD_ODE)
  assert_variable(ANTHEM_LOGGER_NAME "program logger name")
  assert_variable(ANTHEM_WINDOW_NAME "program window name")
endif()

if(BUILD_ODE)
  default_value(ODE_NAME ode_name_not_set)
  default_value(ODE_TEST_NAME test-${ODE_NAME})

  print_status(ODE_NAME "Obliging Ode library name")
  print_status(ODE_TEST_NAME "Obliging Ode test executable name")
else()
  default_value(ANTHEM_NAME name_not_set)
  default_value(ANTHEM_LIB_NAME ${ANTHEM_NAME})
  default_value(ANTHEM_TEST_NAME test-${ANTHEM_NAME})

  print_status(ANTHEM_NAME "executable name")
  print_status(ANTHEM_LIB_NAME "Unsung Anthem library name")
  print_status(ANTHEM_TEST_NAME "Unsung Anthem test executable name")
endif()

print_status_if_defined(ODE_STDLIB "C++ standard library")

print_status_if_defined(ODE_OPTIMIZATION_LEVEL "the optimization level")

set(ODE_STD)
set(ANTHEM_STD)

set_cxx_definitions(${ODE_CXX_VERSION})

print_status(ODE_STD "Obliging Ode C++ standard")
print_status(ANTHEM_STD "Unsung Anthem C++ standard")

set_std_feature_definitions(${ODE_CXX_VERSION})
set_std_flags(${ODE_STD})
add_name_definitions()
add_opengl_definitions()
add_feature_definitions()
add_directory_definitions()

set_compiler_flags()

if(ODE_LINK_LIBCXX)
  set(ODE_LIBRARIES "c++")
else()
  set(ODE_LIBRARIES)
endif()
set(ANTHEM_LIBRARIES)

if(UNIX)
  find_library(SDL2_LIBRARY SDL2)

  assert_variable(SDL2_LIBRARY "SDL2 libraries")

  if(ODE_MANUAL_SDL)
    list(APPEND ODE_LIBRARIES "SDL2maind" "SDL2d")
  else()
    list(APPEND ODE_LIBRARIES "${SDL2_LIBRARY}")
  endif()

  if(APPLE)
    # TODO
  else()
    # set(ODE_LIBRARIES ${ODE_LIBRARIES} SDL2main SDL2 pthread)
    list(APPEND ODE_LIBRARIES "dl" "pthread")
  endif()
else()
  if(WIN32)
    # Presumably Windows.
    list(APPEND ODE_LIBRARIES "opengl32" "SDL2main" "SDL2")
  endif()
endif()

if(NOT ODE_ADD_LUA_SOURCE)
  list(APPEND ODE_LIBRARIES "lua")
endif()

if(ODE_TEST_BENCHMARKING)
  list(APPEND ODE_LIBRARIES "benchmark")
endif()

print_status_plural(ODE_LIBRARIES "libraries")

include_directories(${ODE_INSTALL_PREFIX}/include)
link_directories(${ODE_INSTALL_PREFIX}/lib)

include_directories(include)
include_directories(lib)

# TODO Should the subdirectories in src be set separately for ode and anthem?
include_directories(src)

if(BUILD_ODE)
  if(${ODE_TYPE} STREQUAL test)
    include_directories(test)
  endif()
else()
  if(${ANTHEM_TYPE} STREQUAL test)
    include_directories(test)
  endif()
endif()

set(ODE_LIB_INCLUDES)
set(ODE_INCLUDES)
set(ODE_TEST_INCLUDES)
set(ODE_TEST_SOURCES)
set(ODE_SOURCES)

set(ANTHEM_LIB_INCLUDES)
set(ANTHEM_INCLUDES)
set(ANTHEM_LIB_SOURCES)
set(ANTHEM_TEST_SOURCES)
set(ANTHEM_SOURCES)

set(ODE_TEST_SCRIPTS)
set(ODE_SCRIPTS)

set(ANTHEM_LIB_SCRIPTS)
set(ANTHEM_TEST_SCRIPTS)
set(ANTHEM_SCRIPTS)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(script)
add_subdirectory(test)

set_glad_sources()

if(ODE_ADD_LUA_SOURCE)
  set_lua_sources()
endif()

print_status(CMAKE_CXX_FLAGS "compiler flags")

print_status(ANTHEM_SOURCES "sources")

if(BUILD_ODE)
  create_ode(${ODE_TYPE})
else()
  create_anthem(${ANTHEM_TYPE})
endif()

if(NOT WIN32)
  if(BUILD_ODE)
    add_ode_installation_target(${ODE_TYPE})
  else()
    add_anthem_installation_target(${ANTHEM_TYPE})
  endif()
endif()

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")
message(STATUS
    "The CMake installation prefix is set to ${CMAKE_INSTALL_PREFIX}")
message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")
message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")
