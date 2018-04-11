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

#===------------------------------------------------------------------------===#
#==- Modules ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

include(CompilerFlags)
include(Definitions)
include(ExternalSources)
include(Install)
include(Logging)
include(StdDefinitions)
include(Targets)
include(Variables)

#===------------------------------------------------------------------------===#
#==- Options ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

#==- Obliging Ode Build Options --------------------------------------------===#

option(BUILD_ODE "Build Obliging Ode" OFF)
option(ODE_TEST_BENCHMARKING "Build the benchmarkings in Obliging Ode" OFF)
option(ODE_ENABLE_GCOV "Add target for gcov code coverage" OFF)
option(ODE_LINK_LIBCXX "Manually link libc++" OFF)
option(ODE_ADD_LUA_SOURCE
    "Add Lua source files directly to the Ode sources" OFF)
option(ODE_ADD_GTEST_SOURCE
    "Add Google Test source files directly to the Ode sources" OFF)
option(ODE_ADD_BENCHMARK_SOURCE
    "Add Google Benchmark source files directly to the Ode sources" OFF)
option(ODE_USE_LOCAL_LLVM "Use an LLVM which is in the local directory" OFF)
option(ODE_VERBOSE_BUILD "Print more information while building" OFF)

#==- Obliging Ode Feature Options ------------------------------------------===#

option(ODE_ENABLE_ASSERTIONS
    "Option for enabling assertions in Obliging Ode" ON)
option(ODE_DEVELOPER "Enable developer mode in Obliging Ode" OFF)
option(ODE_SDL_TICK_CLOCK
    "Use SDL clock instead of standard library clock" OFF)
option(ODE_TEST_USE_NULL_SINK "Log the tests to a null sink" ON)
option(ODE_MULTITHREADING "Enable multithreading in the product" ON)
option(ODE_DISABLE_GL_CALLS "Disable the OpenGL calls in Obliging Ode" OFF)

#==- Unsung Anthem Build Options -------------------------------------------===#

option(ANTHEM_TEST_BENCHMARKING "Build the benchmarkings in Unsung Anthem" OFF)

#==- Unsung Anthem Feature Options -----------------------------------------===#

option(ANTHEM_ENABLE_ASSERTIONS
    "Option for enabling assertions in Unsung Anthem" ON)
option(ANTHEM_DEVELOPER "Enable developer mode in Unsung Anthem" OFF)

#===------------------------------------------------------------------------===#
#==- Variable Assertions ---------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(BUILD_ODE)
  assert_variable(ODE_TYPE "Obliging Ode product type" "lib and test")
else()
  assert_variable(ANTHEM_TYPE "Unsung Anthem product type" "exe, lib, and test")
endif()

assert_variable(ODE_CXX_VERSION "C++ standard version" "c++2a and c++17")
assert_variable(ODE_INSTALL_PREFIX "dependency installation directory")
assert_variable(ODE_VERSION "Obliging Ode version")
assert_variable(ANTHEM_VERSION "Unsung Anthem version")
assert_variable(ODE_BIN_DIR_NAME "name of the binary installation directory")
assert_variable(ODE_INCLUDE_DIR_NAME
    "name of the include installation directory")
assert_variable(ODE_LIB_DIR_NAME "name of the library installation directory")
assert_variable(ODE_SCRIPT_DIR_NAME 
    "name of the script installation directory")
assert_variable(ODE_OPENGL_VERSION_MAJOR "OpenGL major version")
assert_variable(ODE_OPENGL_VERSION_MINOR "OpenGL minor version")
assert_variable(ODE_LOGGER_NAME "engine logger name")
assert_variable(ODE_WINDOW_NAME "engine window name")

if(NOT BUILD_ODE)
  assert_variable(ANTHEM_LOGGER_NAME "program logger name")
  assert_variable(ANTHEM_WINDOW_NAME "program window name")
endif()

#===------------------------------------------------------------------------===#
#==- Variable Statuses -----------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_LIB_SCRIPT_DIR_NAME "${ODE_SCRIPT_DIR_NAME}/lib")
set(ODE_TEST_SCRIPT_DIR_NAME "${ODE_SCRIPT_DIR_NAME}/test")

print_status(ODE_LIB_SCRIPT_DIR_NAME "library script installation directory")
print_status(ODE_TEST_SCRIPT_DIR_NAME "test script installation directory")

if(BUILD_ODE)
  default_value(ODE_NAME ode_name_not_set "Obliging Ode library name")
  default_value(ODE_TEST_NAME test-${ODE_NAME}
      "Obliging Ode test executable name")
else()
  default_value(ANTHEM_NAME name_not_set "executable name")
  default_value(ANTHEM_LIB_NAME ${ANTHEM_NAME} "Unsung Anthem library name")
  default_value(ANTHEM_TEST_NAME test-${ANTHEM_NAME}
      "Unsung Anthem test executable name")
endif()

print_status_if_defined(ODE_STDLIB "C++ standard library")
print_status_if_defined(ODE_OPTIMIZATION_LEVEL "the optimization level")
print_status_if_defined(ODE_RPATH "the rpath")

#===------------------------------------------------------------------------===#
#==- Definitions and Flags -------------------------------------------------===#
#===------------------------------------------------------------------------===#

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
set_linker_flags()

#===------------------------------------------------------------------------===#
#==- Libraries -------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_LIBRARIES)
set(ANTHEM_LIBRARIES)

if(NOT ODE_ADD_GTEST_SOURCE)
  if("${ODE_TYPE}" STREQUAL "test" OR "${ANTHEM_TYPE}" STREQUAL "test")
    list(APPEND ODE_LIBRARIES "gtest")
  endif()
endif()

if(ODE_TEST_BENCHMARKING AND NOT ODE_ADD_BENCHMARK_SOURCE)
  list(APPEND ODE_LIBRARIES "benchmark")
endif()

if(ODE_LINK_LIBCXX)
  list(APPEND ODE_LIBRARIES "c++")
endif()

if(UNIX)
  if(APPLE)
    list(APPEND ODE_LIBRARIES "SDL2maind" "SDL2d")
  else()
    list(APPEND ODE_LIBRARIES "SDL2maind" "SDL2d" "dl" "pthread")
  endif()
else()
  if(WIN32)
    list(APPEND ODE_LIBRARIES "opengl32" "SDL2main" "SDL2")
  endif()
endif()

if(NOT ODE_ADD_LUA_SOURCE)
  list(APPEND ODE_LIBRARIES "lua")
endif()

print_status_plural(ODE_LIBRARIES "libraries")

#===------------------------------------------------------------------------===#
#==- Search Paths ----------------------------------------------------------===#
#===------------------------------------------------------------------------===#

print_status(ODE_USE_LOCAL_LLVM "LLVM use status")

if (ODE_USE_LOCAL_LLVM)
  include_directories(${ODE_INSTALL_PREFIX}/include/c++/v1)
endif()

include_directories(${ODE_INSTALL_PREFIX}/include)
link_directories(${ODE_INSTALL_PREFIX}/lib)

include_directories(include)
include_directories(lib)
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

#===------------------------------------------------------------------------===#
#==- Source Files ----------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_LIB_INCLUDES)
set(ODE_INCLUDES)
set(ODE_TEST_INCLUDES)
set(ODE_TEST_SOURCES)
set(ODE_BENCHMARK_SOURCES)
set(ODE_SOURCES)

set(ANTHEM_LIB_INCLUDES)
set(ANTHEM_INCLUDES)
set(ANTHEM_LIB_SOURCES)
set(ANTHEM_TEST_SOURCES)
set(ANTHEM_BENCHMARK_SOURCES)
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

if(ODE_ADD_GTEST_SOURCE)
  if("${ODE_TYPE}" STREQUAL "test" OR "${ANTHEM_TYPE}" STREQUAL "test")
    set_gtest_sources()
    include_directories(${ODE_INSTALL_PREFIX}/src/gtest)
    info("Added the Google Test sources to the testing executable")
  endif()
endif()

if(ODE_TEST_BENCHMARKING AND ODE_ADD_BENCHMARK_SOURCE)
  if("${ODE_TYPE}" STREQUAL "test" OR "${ANTHEM_TYPE}" STREQUAL "test")
    set_benchmark_sources()
    include_directories(${ODE_INSTALL_PREFIX}/src/benchmark)
    info("Added the Google Benchmark sources to the testing executable")
  endif()
endif()

#===------------------------------------------------------------------------===#
#==- Targets ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

default_value(ODE_DYNAMIC_MARK d "dynamic library mark")
default_value(ODE_COVERAGE_MARK c "coverage target mark")

if(BUILD_ODE)
  create_ode(${ODE_TYPE})
else()
  create_anthem(${ANTHEM_TYPE})
endif()

#===------------------------------------------------------------------------===#
#==- Installation Targets --------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(NOT WIN32)
  if(BUILD_ODE)
    add_ode_installation_target(${ODE_TYPE})
  else()
    add_anthem_installation_target(${ANTHEM_TYPE})
  endif()
endif()

#===------------------------------------------------------------------------===#
#==- Compilation and Linking -----------------------------------------------===#
#===------------------------------------------------------------------------===#

if(ODE_VERBOSE_BUILD)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")
endif()

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")
message(STATUS
    "The CMake installation prefix is set to ${CMAKE_INSTALL_PREFIX}")
message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
message(STATUS
    "The C++ executable linker flags are set to ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")
message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")
