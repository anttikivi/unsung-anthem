cmake_minimum_required(VERSION 3.4.3)
project(anthem)

# Check if the executable type (executable or tests) variable is set.
if(NOT DEFINED ANTHEM_EXECUTABLE_TYPE)
  message(FATAL_ERROR "The executable type (ANTHEM_EXECUTABLE_TYPE) is not \
  set – the possible values are 'anthem' and 'test'")
else()
  message(STATUS "The executable type (ANTHEM_EXECUTABLE_TYPE) is set to \
  ${ANTHEM_EXECUTABLE_TYPE}")
endif()

# Check if the installation directory prefix is set.
if(DEFINED ANTHEM_INSTALL_PREFIX)
  message(STATUS "The dependency installation directory \
  (ANTHEM_INSTALL_PREFIX) is set to ${ANTHEM_INSTALL_PREFIX}")
endif()

# Check if the executable name variable is set and if it is not set, set it to
# some stupid default value.
if(NOT DEFINED ANTHEM_EXECUTABLE_NAME)
  set(ANTHEM_EXECUTABLE_NAME unsung-anthem-executable_name_not_set)
endif()

message(STATUS "The executable name (ANTHEM_EXECUTABLE_NAME) is set to \
${ANTHEM_EXECUTABLE_NAME}")

# Check if the C++ Standard version is set.
if(NOT DEFINED ANTHEM_CPP_VERSION)
  message(FATAL_ERROR "The C++ Standard version (ANTHEM_CPP_VERSION) is not \
  set – the possible values are c++17, c++1z, c++14, c++1y, and c++11")
endif()

message(STATUS "The C++ Standard version (ANTHEM_CPP_VERSION) is set to \
${ANTHEM_CPP_VERSION}")

# Set the preprocessor definitions according to the C++ Standard version.
if(${ANTHEM_CPP_VERSION} STREQUAL c++17)

  # Add the definition denoting that C++17 is used.
  add_definitions(-DANTHEM_CPP17)

elseif(${ANTHEM_CPP_VERSION} STREQUAL c++1z)

  # Add the definition denoting that C++1z is used.
  add_definitions(-DANTHEM_CPP17_DRAFT)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CPP17)

elseif(${ANTHEM_CPP_VERSION} STREQUAL c++14)

  # Add the definition denoting that C++14 is used.
  add_definitions(-DANTHEM_CPP14)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CPP17)
  add_definitions(-DANTHEM_DISABLE_CPP17_DRAFT)

elseif(${ANTHEM_CPP_VERSION} STREQUAL c++1y)

  # Add the definition denoting that C++1y is used.
  add_definitions(-DANTHEM_CPP14_DRAFT)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CPP17)
  add_definitions(-DANTHEM_DISABLE_CPP17_DRAFT)
  add_definitions(-DANTHEM_DISABLE_CPP14)

elseif(${ANTHEM_CPP_VERSION} STREQUAL c++11)

  # Add the definition denoting that C++11 is used.
  add_definitions(-DANTHEM_CPP11)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CPP17)
  add_definitions(-DANTHEM_DISABLE_CPP17_DRAFT)
  add_definitions(-DANTHEM_DISABLE_CPP14)
  add_definitions(-DANTHEM_DISABLE_CPP14_DRAFT)

else()

  message(FATAL_ERROR "The C++ Standard version (ANTHEM_CPP_VERSION) is set \
  to ${ANTHEM_CPP_VERSION} and thus it is invalid – the possible values are \
  c++17, c++1z, c++14, c++1y, and c++11")

endif()

# Check the platform for setting the dependencies.
if(UNIX)

  # Add the dependency includes.
  include_directories(${ANTHEM_INSTALL_PREFIX}/include)

  if(APPLE)
  else()
  endif()
else()
endif()

# Add the Unsung Anthem headers to includes.
include_directories(include)

# The variable containing the source files of the project.
set(ANTHEM_INCLUDES)

# Add the source files of the project into single variable from the source
# directory.
add_subdirectory(include)

# Check whether the build is the actual executable or tests.
if (${ANTHEM_EXECUTABLE_TYPE} STREQUAL anthem)

  # The variable containing the source files of the project.
  set(ANTHEM_SOURCES)

  # Add the source files of the project into single variable from the source
  # directory.
  add_subdirectory(src)

  # Add the actual executable with the sources.
  add_executable(${ANTHEM_EXECUTABLE_NAME} ${ANTHEM_INCLUDES} ${ANTHEM_SOURCES})

elseif(${ANTHEM_EXECUTABLE_TYPE} STREQUAL test)
  message(STATUS "This CMake list does not support building tests yet")
else()
  message(FATAL_ERROR "The value of the executable type \
  (ANTHEM_EXECUTABLE_TYPE) is ${ANTHEM_EXECUTABLE_TYPE} and thus invalid – \
  please set it to either 'anthem' or 'test'")
endif()
