cmake_minimum_required(VERSION 2.8.12)
project(anthem)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

option(ANTHEM_CUSTOM_LIBCXX "Use alternative installation of libc++" OFF)

option(ANTHEM_ENABLE_ASSERTIONS "Option for enabling assertions in the code" ON)

option(ANTHEM_SDL "Use SDL to build Unsung Anthem" OFF)
option(ANTHEM_GLFW "Use GLFW to build Unsung Anthem" OFF)

option(ANTHEM_USE_EXPERIMENTAL_HEADERS "Use experimental C++ standard headers" OFF)

option(ANTHEM_ENABLE_GCOV "Add target for gcov code coverage" OFF)

# Check if the executable type (executable or tests) variable is set.
if(NOT DEFINED ANTHEM_EXECUTABLE_TYPE)
  message(FATAL_ERROR "The executable type (ANTHEM_EXECUTABLE_TYPE) is not set – the possible values are 'anthem' and 'test'")
else()
  message(STATUS "The executable type (ANTHEM_EXECUTABLE_TYPE) is set to ${ANTHEM_EXECUTABLE_TYPE}")
endif()

# Check if the installation directory prefix is set.
if(DEFINED ANTHEM_INSTALL_PREFIX)
  message(STATUS "The dependency installation directory (ANTHEM_INSTALL_PREFIX) is set to ${ANTHEM_INSTALL_PREFIX}")
endif()

# Check if the executable name variable is set and if it is not set, set it to
# some stupid default value.
if(NOT DEFINED ANTHEM_EXECUTABLE_NAME)
  set(ANTHEM_EXECUTABLE_NAME unsung-anthem-executable_name_not_set)
endif()

message(STATUS "The executable name (ANTHEM_EXECUTABLE_NAME) is set to ${ANTHEM_EXECUTABLE_NAME}")

# Check if the test executable name variable is set and if it is not set, set
# it to some stupid default value.
if(NOT DEFINED ANTHEM_TEST_EXECUTABLE_NAME)
  set(ANTHEM_TEST_EXECUTABLE_NAME test-${ANTHEM_EXECUTABLE_NAME})
endif()

message(STATUS "The test executable name (ANTHEM_TEST_EXECUTABLE_NAME) is set to ${ANTHEM_TEST_EXECUTABLE_NAME}")

# Check if the C++ Standard version is set.
if(NOT DEFINED ANTHEM_CXX_VERSION)
  message(FATAL_ERROR "The C++ standard version (ANTHEM_CXX_VERSION) is not set – the possible values are c++2a, c++17, c++14, and c++latest")
endif()

message(STATUS "The C++ standard version (ANTHEM_CXX_VERSION) is set to ${ANTHEM_CXX_VERSION}")

# Check if the C++ standard library is set.
if(DEFINED ANTHEM_STDLIB)
  message(STATUS "The C++ standard library (ANTHEM_STDLIB) is set to ${ANTHEM_STDLIB}")
endif()

# Check if the main build tool is set.
if(NOT DEFINED ANTHEM_MAIN_COMPILER_TOOL)
  message(FATAL_ERROR "The main tool for the build (ANTHEM_MAIN_COMPILER_TOOL) is not set – the possible values are llvm, gcc, and msbuild")
endif()

message(STATUS "The main tool for the build (ANTHEM_MAIN_COMPILER_TOOL) is set to ${ANTHEM_MAIN_COMPILER_TOOL}")

# Check if the executable type (executable or tests) variable is set.
if(NOT DEFINED ANTHEM_SDL AND NOT DEFINED ANTHEM_GLFW)
  message(FATAL_ERROR "The neither SDL nor GLFW (ANTHEM_SDL and ANTHEM_GLFW) is not set")
elseif(ANTHEM_SDL AND ANTHEM_GLFW)
  message(FATAL_ERROR "The both SDL and GLFW (ANTHEM_SDL and ANTHEM_GLFW) are used")
elseif(NOT ANTHEM_SDL AND NOT ANTHEM_GLFW)
  message(FATAL_ERROR "The neither SDL nor GLFW (ANTHEM_SDL and ANTHEM_GLFW) is used")
endif()

# Set the preprocessor definition for the main tool.
if(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL msbuild)
  add_definitions(-DANTHEM_MSBUILD)
elseif(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL gcc)
  add_definitions(-DANTHEM_GCC)
elseif(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL llvm)
  add_definitions(-DANTHEM_CLANG)
endif()

if(ANTHEM_USE_EXPERIMENTAL_HEADERS)
  add_definitions(-DANTHEM_EXPERIMENTAL_HEADERS)
endif()

# Set the preprocessor definitions according to the C++ standard version.
if(${ANTHEM_CXX_VERSION} STREQUAL c++latest)

  # Add the definition denoting C++17 is used.
  add_definitions(-DANTHEM_CXX17)

  # Add the variable for setting the C++ standard version to the compiler.
  if(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL msbuild)
    set(ANTHEM_STD c++latest)
  elseif(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL gcc)
    set(ANTHEM_STD c++17)
  elseif(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL llvm)
    set(ANTHEM_STD c++1z)
  endif()

elseif(${ANTHEM_CXX_VERSION} STREQUAL c++2a)

  # Add the definition denoting the next C++ standard draft is used.
  add_definitions(-DANTHEM_CXX2A)

  # Add the variable for setting the C++ standard version to the compiler.
  # TODO Any compiler does not implement C++2a yet.
  if(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL llvm)
    set(ANTHEM_STD c++1z)
  else()
    set(ANTHEM_STD c++17)
  endif()

elseif(${ANTHEM_CXX_VERSION} STREQUAL c++17)

  # Add the definition denoting C++17 is used.
  add_definitions(-DANTHEM_CXX17)

  # Add the variable for setting the C++ standard version to the compiler.
  if(${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL llvm)
    set(ANTHEM_STD c++1z)
  else()
    set(ANTHEM_STD c++17)
  endif()

elseif(${ANTHEM_CXX_VERSION} STREQUAL c++14)

  # Add the definition denoting C++14 is used.
  add_definitions(-DANTHEM_CXX14)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CXX17)

  # Add the variable for setting the C++ standard version to the compiler.
  set(ANTHEM_STD ${ANTHEM_CXX_VERSION})

else()

  message(FATAL_ERROR "The C++ standard version (ANTHEM_CXX_VERSION) is set to ${ANTHEM_CXX_VERSION} and thus it is invalid – the possible values are c++2a, c++17, c++14, and c++latest")

endif()

# Set the C++ compiler flags.
if (WIN32)
  # TODO Set these kinds of flags if the build is done with MSBuild on any
  # platform.
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std=${ANTHEM_STD}")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${ANTHEM_STD}")
endif()

if (DEFINED ANTHEM_STDLIB)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=${ANTHEM_STDLIB}")
endif()

if(ANTHEM_CUSTOM_LIBCXX)
  # set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -nostdinc++ -I${ANTHEM_INSTALL_PREFIX}/include/c++/v1 -L${ANTHEM_INSTALL_PREFIX}/lib -Wl,-rpath,${ANTHEM_INSTALL_PREFIX}/lib -lc++")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -I${ANTHEM_INSTALL_PREFIX}/include/c++/v1")
endif()

message(STATUS "The CMake build type is set to ${CMAKE_BUILD_TYPE}")

message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")

message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")

message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")

# Check the platform for setting the dependencies.
if(UNIX)

  # Add the dependency includes.
  # include_directories(${ANTHEM_INSTALL_PREFIX}/include)

  if(APPLE)
  else()
  endif()
else()
endif()

# Add the dependency includes.
include_directories(${ANTHEM_INSTALL_PREFIX}/include)

# Add the Unsung Anthem headers to includes.
include_directories(include)
include_directories(lib)
include_directories(src)

# The variable containing the library include files of the project.
set(ANTHEM_LIB_INCLUDES)

# The variable containing the include files of the project.
set(ANTHEM_INCLUDES)

# The variable containing the library source files of the project.
set(ANTHEM_LIB_SOURCES)

# The variable containing the source files of the project tests.
set(ANTHEM_TEST_SOURCES)

# The variable containing the source files of the project.
set(ANTHEM_SOURCES)

# Add the source files of the project into single variable from the source
# directory.
add_subdirectory(include)

# Add the library source files of the project into single variable from the
# library directory.
add_subdirectory(lib)

# Add the source files of the project into single variable from the source
# directory.
add_subdirectory(src)

# Add the source files of the project into single variable from the source
# directory.
add_subdirectory(test)

# Check whether the build is the actual executable or tests.
if(${ANTHEM_EXECUTABLE_TYPE} STREQUAL anthem)

  # Add the actual executable with the sources.
  add_executable(${ANTHEM_EXECUTABLE_NAME}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_SOURCES})

elseif(${ANTHEM_EXECUTABLE_TYPE} STREQUAL test)

  # Remove the main function of the executable from the tests as the tests need
  # their own main function.
  list(REMOVE_ITEM ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

  # Add the actual executable with the sources.
  add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_TEST_SOURCES}
      ${ANTHEM_SOURCES})

  if (ANTHEM_ENABLE_GCOV)

    include(CodeCoverage)

    # set(COVERAGE_EXCLUDES "${ANTHEM_INSTALL_PREFIX}/include" "/usr/include" "v1" "v1/experimental")

    setup_target_for_coverage(NAME ${ANTHEM_EXECUTABLE_NAME}_coverage
      EXECUTABLE ${ANTHEM_TEST_EXECUTABLE_NAME})
  endif()

elseif(${ANTHEM_EXECUTABLE_TYPE} STREQUAL clion)

  # Add the actual executable with the sources.
  add_executable(${ANTHEM_EXECUTABLE_NAME}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_SOURCES})

  # Remove the main function of the executable from the tests as the tests need
  # their own main function.
  list(REMOVE_ITEM ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

  # Add the actual executable with the sources.
  add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_TEST_SOURCES}
      ${ANTHEM_SOURCES})

else()
  message(FATAL_ERROR "The value of the executable type (ANTHEM_EXECUTABLE_TYPE) is ${ANTHEM_EXECUTABLE_TYPE} and thus invalid – please set it to either 'anthem' or 'test'")
endif()
