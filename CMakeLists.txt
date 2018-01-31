#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
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

option(BUILD_ODE "Build the Ode engine" OFF)

option(ODE_ENABLE_GCOV "Add target for gcov code coverage" OFF)

option(ODE_ENABLE_ASSERTIONS
    "Option for enabling assertions in Ode" ON)

option(ANTHEM_ENABLE_ASSERTIONS
    "Option for enabling assertions in Unsung Anthem" ON)

option(ODE_LINK_LIBCXX "Option for linking against libc++ and libc++abi" OFF)

option(ODE_MULTITHREADING "Enable multithreading in the game" ON)

option(ODE_MANUAL_SDL "Simple DirectMedia Layer is linked manually" OFF)

if(BUILD_ODE)
  assert_variable(ODE_TYPE "Ode product type" "lib and test")
else()
  assert_variable(ANTHEM_TYPE "Unsung Anthem product type" "exe, lib, and test")
endif()

assert_variable(ODE_CXX_VERSION
    "C++ standard version"
    "c++2a, c++17, c++14, and c++latest")
assert_variable(ODE_MAIN_COMPILER_TOOL
    "main tool for the Ode build"
    "llvm, gcc, and msbuild")

assert_variable(ODE_INSTALL_PREFIX "dependency installation directory")

assert_variable(ODE_OPENGL_VERSION_MAJOR "OpenGL major version")
assert_variable(ODE_OPENGL_VERSION_MINOR "OpenGL minor version")

assert_variable(ODE_LOGGER_NAME "the engine logger name")

if(NOT BUILD_ODE)
  assert_variable(ANTHEM_LOGGER_NAME "program logger name")
  assert_variable(ANTHEM_WINDOW_NAME "program window name")
endif()

if(BUILD_ODE)
  default_value(ODE_NAME ode_name_not_set)
  default_value(ODE_TEST_NAME test-${ODE_NAME})

  print_status(ODE_NAME "Ode library name")
  print_status(ODE_TEST_NAME "Ode test executable name")
else()
  default_value(ANTHEM_NAME name_not_set)
  default_value(ANTHEM_LIB_NAME ${ANTHEM_NAME})
  default_value(ANTHEM_TEST_NAME test-${ANTHEM_NAME})

  print_status(ANTHEM_NAME "executable name")
  print_status(ANTHEM_LIB_NAME "Unsung Anthem library name")
  print_status(ANTHEM_TEST_NAME "Unsung Anthem test executable name")
endif()

print_status_if_defined(ODE_STDLIB "C++ standard library")

set_cxx_definitions(${ODE_CXX_VERSION})
set_std_feature_definitions(${ODE_CXX_VERSION})
set_std_flags(${ODE_STD})
add_name_definitions()

set(ODE_LIBRARIES)
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

if(ODE_LINK_LIBCXX)
  list(APPEND ODE_LIBRARIES "c++abi")
  message(STATUS "Linking against libc++ and libc++abi")
endif()

print_status_plural(ODE_LIBRARIES "libraries")

include_directories(${ODE_INSTALL_PREFIX}/include)
link_directories(${ODE_INSTALL_PREFIX}/lib)

include_directories(include)
include_directories(lib)

# TODO Should the subdirectories in src be set separately for ode and anthem?
include_directories(src)

set(ODE_LIB_INCLUDES)
set(ODE_INCLUDES)
set(ODE_TEST_SOURCES)
set(ODE_SOURCES)

set(ANTHEM_LIB_INCLUDES)
set(ANTHEM_INCLUDES)
set(ANTHEM_LIB_SOURCES)
set(ANTHEM_TEST_SOURCES)
set(ANTHEM_SOURCES)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

set_glad_sources()

print_status(CMAKE_CXX_FLAGS "compiler flags")

print_status(ANTHEM_SOURCES "sources")

if(BUILD_ODE)
  create_ode(${ODE_TYPE})
else()
  create_anthem(${ANTHEM_TYPE})
endif()

if(BUILD_ODE)
  add_ode_installation_target(${ODE_TYPE})
else()
  add_anthem_installation_target(${ANTHEM_TYPE})
endif()

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")
message(STATUS
    "The CMake installation prefix is set to ${CMAKE_INSTALL_PREFIX}")
message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")
message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")
