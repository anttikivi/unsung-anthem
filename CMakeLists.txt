#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

cmake_minimum_required(VERSION 2.8.12)
project(anthem)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

#===------------------------------------------------------------------------===#
#==- Modules ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

include(CompilerFlags)
include(Definitions)
include(ExternalSources)
include(Install)
include(StdDefinitions)
include(Targets)
include(Variables)

#===------------------------------------------------------------------------===#
#==- CMake Variables -------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)

#===------------------------------------------------------------------------===#
#==- Options ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

#==- Obliging Ode Build Options --------------------------------------------===#

option(ODE_BUILD_TEST "Build the tests" OFF)
option(ODE_TEST_BENCHMARKING "Build the benchmarkings" OFF)
option(ODE_ENABLE_GCOV "Add target for gcov code coverage" OFF)
option(ODE_BUILD_STATIC "Build the static Obliging Ode library" OFF)
option(ODE_BUILD_SHARED "Build the shared Obliging Ode library" OFF)
option(ODE_USE_SDL_DEBUG_SUFFIX
    "Link Obliging Ode against SDL with debug suffix on Windows builds" OFF)
option(ODE_ADD_GOOGLE_TEST_SOURCE
    "Build Google Test source files with the Obliging Ode sources" OFF)

#==- Unsung Anthem Build Options -------------------------------------------===#

option(ANTHEM_BUILD_STATIC "Build the static Unsung Anthem library" OFF)
option(ANTHEM_BUILD_SHARED "Build the shared Unsung Anthem library" OFF)

#==- Obliging Ode Feature Options ------------------------------------------===#

option(ODE_ENABLE_ASSERTIONS "Option for enabling assertions" ON)
option(ODE_DEVELOPER "Enable developer mode" OFF)
option(ODE_STD_CLOCK
    "Use the C++ standard library clock instead of the SDL clock" OFF)
option(ODE_TEST_USE_NULL_SINK "Log the tests to a null sink" ON)
option(ODE_MULTITHREADING "Enable multithreading in the product" ON)
option(ODE_DISABLE_GL_CALLS "Disable the OpenGL calls in Obliging Ode" OFF)

#===------------------------------------------------------------------------===#
#==- Variable Assertions ---------------------------------------------------===#
#===------------------------------------------------------------------------===#

assert_variable(ODE_CXX_VERSION "C++ standard version" "c++2a and c++17")
assert_variable(ODE_DEPENDENCY_PREFIX "dependency installation directory")
assert_variable(ODE_VERSION "Obliging Ode version")
assert_variable(ANTHEM_VERSION "Unsung Anthem version")
assert_variable(ODE_OPENGL_VERSION_MAJOR "OpenGL major version")
assert_variable(ODE_OPENGL_VERSION_MINOR "OpenGL minor version")
assert_variable(ODE_LOGGER_NAME "engine logger name")
assert_variable(ODE_WINDOW_NAME "engine window name")
assert_variable(ANTHEM_LOGGER_NAME "program logger name")
assert_variable(ANTHEM_WINDOW_NAME "program window name")

#===------------------------------------------------------------------------===#
#==- Conditional Variable Assertions ---------------------------------------===#
#===------------------------------------------------------------------------===#

if(ODE_ADD_GOOGLE_TEST_SOURCE)
  assert_variable(ODE_GOOGLE_TEST_DIRECTORY "Google Test source directory")
endif()

#===------------------------------------------------------------------------===#
#==- Variable Statuses -----------------------------------------------------===#
#===------------------------------------------------------------------------===#

default_value(ODE_NAME ode-name_not_set "Obliging Ode binaries name")
default_value(ODE_LIB_NAME ${ODE_NAME} "Obliging Ode library name")

default_value(ANTHEM_NAME anthem-name_not_set "executable name")
default_value(ANTHEM_LIB_NAME ${ANTHEM_NAME} "Unsung Anthem library name")
default_value(ANTHEM_TEST_NAME test-${ANTHEM_NAME}
    "Unsung Anthem test executable name")

print_status_if_defined(ODE_STDLIB "C++ standard library")
print_status_if_defined(ODE_RPATH "the rpath")

print_status_if_defined(ODE_MSVC_RUNTIME_LIBRARY "the MSVC runtime library")

#===------------------------------------------------------------------------===#
#==- Definitions and Flags -------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_STD)

set_cxx_definitions(${ODE_CXX_VERSION})
set_std_feature_definitions(${ODE_CXX_VERSION})

print_status(ODE_STD "Obliging Ode C++ standard")

set_std_flags(${ODE_STD})
set_linker_flags()

add_name_definitions()
add_opengl_definitions()
add_directory_definitions()
add_feature_definitions()

#===------------------------------------------------------------------------===#
#==- Libraries -------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_LIBRARIES)

if(NOT WIN32)
  message(STATUS "Looking for SDL libraries")
  find_package(SDL2 REQUIRED HINTS ${ODE_DEPENDENCY_PREFIX})
  list(APPEND ODE_LIBRARIES ${SDL2_LIBRARIES})
endif()

if(ODE_BUILD_TEST AND NOT ODE_ADD_GOOGLE_TEST_SOURCE)
  message(STATUS "Looking for Google Test libraries")
  find_library(GTEST_LIBRARY gtestd HINTS "${ODE_DEPENDENCY_PREFIX}/lib")
  list(APPEND ODE_LIBRARIES ${GTEST_LIBRARY})
elseif(ODE_BUILD_TEST AND ODE_ADD_GOOGLE_TEST_SOURCE)
  list(APPEND ODE_LIBRARIES "gtest")
endif()

if(ODE_TEST_BENCHMARKING)
  message(STATUS "Looking for Google Benchmark libraries")
  find_library(BENCHMARK_LIBRARY benchmark
      HINTS "${ODE_DEPENDENCY_PREFIX}/lib")
  list(APPEND ODE_LIBRARIES ${BENCHMARK_LIBRARY})
endif()

if(UNIX)
  if(NOT APPLE)
    message(STATUS "Setting threading libraries manually")
    list(APPEND ODE_LIBRARIES "dl" "pthread")
  endif()
else()
  if(WIN32)
    message(STATUS "Setting SDL libraries manually")
    if(ODE_USE_SDL_DEBUG_SUFFIX)
      message(STATUS "Linking against SDL libraries with debug suffix")
      list(APPEND ODE_LIBRARIES "opengl32" "SDL2maind" "SDL2d")
    else()
      list(APPEND ODE_LIBRARIES "opengl32" "SDL2main" "SDL2")
    endif()
  endif()
endif()

find_library(LUA_LIBRARY lua HINTS "${ODE_DEPENDENCY_PREFIX}/lib")

list(APPEND ODE_LIBRARIES ${LUA_LIBRARY})

print_status_plural(ODE_LIBRARIES "libraries")

#===------------------------------------------------------------------------===#
#==- Search Paths ----------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(WIN32)
  link_directories(${ODE_DEPENDENCY_PREFIX}/lib)
endif()

if(NOT WIN32)
  include_directories(${SDL2_INCLUDE_DIRS})
endif()

include_directories(${ODE_DEPENDENCY_PREFIX}/include)

include_directories(include)
include_directories(lib)
include_directories(src)

if(ODE_BUILD_TEST)
  include_directories(test)
endif()

#===------------------------------------------------------------------------===#
#==- Source Files ----------------------------------------------------------===#
#===------------------------------------------------------------------------===#

set(ODE_INCLUDES)
set(ODE_LIB_INCLUDES)
set(ODE_TEST_INCLUDES)
set(ODE_SOURCES)
set(ODE_TEST_SOURCES)
set(ODE_BENCHMARK_SOURCES)

set(ANTHEM_INCLUDES)
set(ANTHEM_LIB_INCLUDES)
set(ANTHEM_SOURCES)
set(ANTHEM_LIB_SOURCES)
set(ANTHEM_TEST_SOURCES)
set(ANTHEM_BENCHMARK_SOURCES)

set(ODE_SCRIPTS)
set(ODE_TEST_SCRIPTS)

set(ANTHEM_SCRIPTS)
set(ANTHEM_LIB_SCRIPTS)
set(ANTHEM_TEST_SCRIPTS)

add_subdirectory(include)
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(script)
add_subdirectory(test)

set_glad_sources()

if(ODE_ADD_GOOGLE_TEST_SOURCE)
  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  add_subdirectory(${ODE_GOOGLE_TEST_DIRECTORY})
endif()

#===------------------------------------------------------------------------===#
#==- Targets ---------------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(DEFINED ODE_RPATH AND APPLE)
  set(CMAKE_MACOSX_RPATH 1)
endif()

default_value(ODE_DYNAMIC_MARK d "dynamic library mark")
default_value(ODE_COVERAGE_MARK c "coverage target mark")

create_targets()

#===------------------------------------------------------------------------===#
#==- Install Targets -------------------------------------------------------===#
#===------------------------------------------------------------------------===#

if(NOT WIN32)
  create_install_targets()
endif()

#===------------------------------------------------------------------------===#
#==- Compilation and Linking -----------------------------------------------===#
#===------------------------------------------------------------------------===#

# TODO Consider adding the option
if(ODE_VERBOSE_BUILD)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -v")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -v")
endif()

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")
message(STATUS
    "The CMake installation prefix is set to ${CMAKE_INSTALL_PREFIX}")
message(STATUS
    "The CMake library installation prefix is set to ${CMAKE_INSTALL_LIBDIR}")
message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
message(STATUS
    "The C++ executable linker flags are set to ${CMAKE_EXE_LINKER_FLAGS}")
message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")
message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")

get_directory_property(COMPILE_DEFS COMPILE_DEFINITIONS)

message(STATUS "The compile definitions are ${COMPILE_DEFS}")
