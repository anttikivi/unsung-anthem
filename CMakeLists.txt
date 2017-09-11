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
include(Executables)
include(StdDefinitions)
include(Variables)

option(ANTHEM_ENABLE_ASSERTIONS
    "Option for enabling assertions in the code" ON)

option(ANTHEM_SDL "Use SDL to build Unsung Anthem" OFF)
option(ANTHEM_GLFW "Use GLFW to build Unsung Anthem" OFF)

option(ANTHEM_ENABLE_GCOV "Add target for gcov code coverage" OFF)

assert_variable(ANTHEM_EXECUTABLE_TYPE
    "executable type"
    "anthem, test, and clion")
assert_variable(ANTHEM_CXX_VERSION
    "C++ standard version"
    "c++2a, c++17, c++14, and c++latest")
assert_variable(ANTHEM_MAIN_COMPILER_TOOL
    "main tool for the build"
    "llvm, gcc, and msbuild")

assert_variable(ANTHEM_INSTALL_PREFIX "dependency installation directory")

default_value(ANTHEM_EXECUTABLE_NAME executable_name_not_set)
default_value(ANTHEM_TEST_EXECUTABLE_NAME test-${ANTHEM_EXECUTABLE_NAME})

print_status(ANTHEM_EXECUTABLE_NAME "executable name")
print_status(ANTHEM_TEST_EXECUTABLE_NAME "test executable name")

print_status_if_defined(ANTHEM_STDLIB "C++ standard library")

assert_only_other(ANTHEM_SDL ANTHEM_GLFW SDL GLFW)

set_cxx_definitions(${ANTHEM_CXX_VERSION})
set_std_feature_definitions(${ANTHEM_CXX_VERSION})
set_std_flags(${ANTHEM_STD})

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")
message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")
message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")

if(UNIX)

  # Add the dependency includes.
  # include_directories(${ANTHEM_INSTALL_PREFIX}/include)

  if(APPLE)
  else()
  endif()
else()
endif()

include_directories(${ANTHEM_INSTALL_PREFIX}/include)

include_directories(include)
include_directories(lib)
include_directories(src)

set(ANTHEM_LIB_INCLUDES)
set(ANTHEM_INCLUDES)
set(ANTHEM_LIB_SOURCES)
set(ANTHEM_TEST_SOURCES)
set(ANTHEM_SOURCES)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)

create_executable(${ANTHEM_EXECUTABLE_TYPE})
