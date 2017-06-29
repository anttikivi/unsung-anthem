cmake_minimum_required(VERSION 3.4.3)
project(anthem)

# Check if the executable type (executable or tests) variable is set.
if(NOT DEFINED ANTHEM_EXECUTABLE_TYPE)
  message(FATAL_ERROR "The executable type (ANTHEM_EXECUTABLE_TYPE) is not set – the possible values are 'anthem' and \
          'test'")
else()
  message(STATUS "The executable type (ANTHEM_EXECUTABLE_TYPE) is set to ${ANTHEM_EXECUTABLE_TYPE}")
endif()

# Check if the installation directory prefix is set.
if(DEFINED ANTHEM_INSTALL_PREFIX)
  message(STATUS "The dependency installation directory (ANTHEM_INSTALL_PREFIX) is set to ${ANTHEM_INSTALL_PREFIX}")
endif()

# Check if the executable name variable is set and if it is not set, set it to some stupid default value.
if(NOT DEFINED ANTHEM_EXECUTABLE_NAME)
  set(ANTHEM_EXECUTABLE_NAME unsung-anthem-executable_name_not_set)
endif()

message(STATUS "The executable name (ANTHEM_EXECUTABLE_NAME) is set to ${ANTHEM_EXECUTABLE_NAME}")

# Check whether the build is the actual executable or tests.
if (${ANTHEM_EXECUTABLE_TYPE} MATCHES anthem)

  # The variable containing the source files of the project.
  set(ANTHEM_SOURCES)

  # Add the source files of the project into single variable from the source directory.
  add_subdirectory(src)

  # Add the actual executable with the sources.
  add_executable(${ANTHEM_EXECUTABLE_NAME} ${ANTHEM_SOURCES})

elseif(${ANTHEM_EXECUTABLE_TYPE} MATCHES test)
  message(STATUS "This CMake list does not support building tests yet")
else()
  message(FATAL_ERROR "The value of the executable type (ANTHEM_EXECUTABLE_TYPE) is ${ANTHEM_EXECUTABLE_TYPE} and thus \
          invalid – please set it to either 'anthem' or 'test'")
endif()
