cmake_minimum_required(VERSION 3.4.3)
project(anthem)

option(ANTHEM_DEFAULT_COMPILER
    "Option for using the default system compiler so the CMake script does not
 give error when some of the definitions are missing"
    OFF)

option(ANTHEM_LLVM OFF)

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

# Check if the test executable name variable is set and if it is not set, set
# it to some stupid default value.
if(NOT DEFINED ANTHEM_TEST_EXECUTABLE_NAME)
  set(ANTHEM_TEST_EXECUTABLE_NAME test-${ANTHEM_EXECUTABLE_NAME})
endif()

message(STATUS "The test executable name (ANTHEM_TEST_EXECUTABLE_NAME) is set \
to ${ANTHEM_TEST_EXECUTABLE_NAME}")

# Check if the C++ Standard version is set.
if(NOT DEFINED ANTHEM_CPP_VERSION)
  message(FATAL_ERROR "The C++ standard version (ANTHEM_CPP_VERSION) is not \
  set – the possible values are c++17, c++1z, c++14, c++1y, and c++11")
endif()

message(STATUS "The C++ standard version (ANTHEM_CPP_VERSION) is set to \
${ANTHEM_CPP_VERSION}")

# Check if the C++ standard library is set.
if(NOT ANTHEM_DEFAULT_COMPILER AND NOT DEFINED ANTHEM_STDLIB)
  message(FATAL_ERROR "The C++ standard library (ANTHEM_STDLIB) is not set – \
  the possible values are libc++ and libstdc++")
endif()

message(STATUS "The C++ standard library (ANTHEM_STDLIB) is set to \
${ANTHEM_STDLIB}")

# Set the compiler flags which will be set if the build is done with LLVM.
set(LLVM_CXX_FLAGS "-stdlib=${ANTHEM_STDLIB} -nostdinc++ -I${ANTHEM_INSTALL_PREFIX}/include/c++/v1 -L${ANTHEM_INSTALL_PREFIX}/lib -Wl,-rpath,${ANTHEM_INSTALL_PREFIX}/lib")

# Set the preprocessor definitions according to the C++ Standard version.
if(${ANTHEM_CPP_VERSION} STREQUAL c++17)

  # Add the definition denoting that C++17 is used.
  add_definitions(-DANTHEM_CPP17)

  # Add the variable for setting the C++ standard version to the compiler.
  set(ANTHEM_STD c++1z)

elseif(${ANTHEM_CPP_VERSION} STREQUAL c++1z)

  # Add the definition denoting that C++1z is used.
  add_definitions(-DANTHEM_CPP17_DRAFT)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CPP17)

  # Add the variable for setting the C++ standard version to the compiler.
  set(ANTHEM_STD ${ANTHEM_CPP_VERSION})

elseif(${ANTHEM_CPP_VERSION} STREQUAL c++14)

  # Add the definition denoting that C++14 is used.
  add_definitions(-DANTHEM_CPP14)

  # Add the definition for the disabled newer version of C++ Standard.
  add_definitions(-DANTHEM_DISABLE_CPP17)
  add_definitions(-DANTHEM_DISABLE_CPP17_DRAFT)

  # Add the variable for setting the C++ standard version to the compiler.
  set(ANTHEM_STD ${ANTHEM_CPP_VERSION})

elseif(${ANTHEM_CPP_VERSION} STREQUAL all)

  message(STATUS "The C++ standard version (ANTHEM_CPP_VERSION) is set to ${ANTHEM_CPP_VERSION} – the executable will be built against C++17 and C++14")

else()

  message(FATAL_ERROR "The C++ standard version (ANTHEM_CPP_VERSION) is set \
  to ${ANTHEM_CPP_VERSION} and thus it is invalid – the possible values are \
  c++17 and c++14")

endif()

# Set the C++ compiler flags if the build is not done against all C++
# standard versions.
if(NOT ${ANTHEM_CPP_VERSION} STREQUAL all)

  if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std=${ANTHEM_STD}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${ANTHEM_STD}")
  endif()

  if(ANTHEM_LLVM)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")
  endif()

  message(STATUS "The C++ compile flags are set to ${CMAKE_CXX_FLAGS}")
else()
  if(ANTHEM_LLVM)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${LLVM_CXX_FLAGS}")
  endif()

    # TODO Windows

  set(ANTHEM_CPP17_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
  set(ANTHEM_CPP14_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

message(STATUS "The C compiler flag is set to ${CMAKE_C_COMPILER}")
message(STATUS "The C++ compiler flag is set to ${CMAKE_CXX_COMPILER}")

message(STATUS "The C compiler environment variable is set to $ENV{CC}")
message(STATUS "The C++ compiler environment variable is set to $ENV{CXX}")

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

  if(${ANTHEM_CPP_VERSION} STREQUAL all)

    # Add the actual executable with the sources and C++17 properties.
    add_executable(${ANTHEM_EXECUTABLE_NAME}-cxx17
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_EXECUTABLE_NAME}-cxx17 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP17_FLAGS})

    target_compile_definitions(${ANTHEM_EXECUTABLE_NAME}-cxx17 PRIVATE ANTHEM_CPP17)

    # Add the actual executable with the sources and C++14 properties.
    add_executable(${ANTHEM_EXECUTABLE_NAME}-cxx14
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_EXECUTABLE_NAME}-cxx14 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP14_FLAGS})

    target_compile_definitions(${ANTHEM_EXECUTABLE_NAME}-cxx14 PRIVATE ANTHEM_CPP14 ANTHEM_DISABLE_CPP17 ANTHEM_DISABLE_CPP17_DRAFT)

  else()

    # Add the actual executable with the sources.
    add_executable(${ANTHEM_EXECUTABLE_NAME}
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_SOURCES})

  endif()

elseif(${ANTHEM_EXECUTABLE_TYPE} STREQUAL test)

  # Remove the main function of the executable from the tests as the tests need
  # their own main function.
  list(REMOVE_ITEM ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

  if(${ANTHEM_CPP_VERSION} STREQUAL all)

    # Add the actual executable with the sources and C++17 properties.
    add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx17
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx17 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP17_FLAGS})

    target_compile_definitions(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx17 PRIVATE ANTHEM_CPP17)

    # Add the actual executable with the sources and C++14 properties.
    add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx14
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx14 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP14_FLAGS})

    target_compile_definitions(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx14 PRIVATE ANTHEM_CPP14 ANTHEM_DISABLE_CPP17 ANTHEM_DISABLE_CPP17_DRAFT)

  else()

    # Add the actual executable with the sources.
    add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})
  endif()

elseif(${ANTHEM_EXECUTABLE_TYPE} STREQUAL clion)

  if(${ANTHEM_CPP_VERSION} STREQUAL all)

    # Add the actual executable with the sources and C++17 properties.
    add_executable(${ANTHEM_EXECUTABLE_NAME}-cxx17
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_EXECUTABLE_NAME}-cxx17 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP17_FLAGS})

    target_compile_definitions(${ANTHEM_EXECUTABLE_NAME}-cxx17 PRIVATE ANTHEM_CPP17)

    # Add the actual executable with the sources and C++14 properties.
    add_executable(${ANTHEM_EXECUTABLE_NAME}-cxx14
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_EXECUTABLE_NAME}-cxx14 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP14_FLAGS})

    target_compile_definitions(${ANTHEM_EXECUTABLE_NAME}-cxx14 PRIVATE ANTHEM_CPP14 ANTHEM_DISABLE_CPP17 ANTHEM_DISABLE_CPP17_DRAFT)

  else()

    # Add the actual executable with the sources.
    add_executable(${ANTHEM_EXECUTABLE_NAME}
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_SOURCES})

  endif()

  # Remove the main function of the executable from the tests as the tests need
  # their own main function.
  list(REMOVE_ITEM ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)

  if(${ANTHEM_CPP_VERSION} STREQUAL all)

    # Add the actual executable with the sources and C++17 properties.
    add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx17
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx17 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP17_FLAGS})

    target_compile_definitions(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx17 PRIVATE ANTHEM_CPP17)

    # Add the actual executable with the sources and C++14 properties.
    add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx14
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})

    set_target_properties(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx14 PROPERTIES COMPILE_FLAGS ${ANTHEM_CPP14_FLAGS})

    target_compile_definitions(${ANTHEM_TEST_EXECUTABLE_NAME}-cxx14 PRIVATE ANTHEM_CPP14 ANTHEM_DISABLE_CPP17 ANTHEM_DISABLE_CPP17_DRAFT)

  else()

    # Add the actual executable with the sources.
    add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})

  endif()

else()
  message(FATAL_ERROR "The value of the executable type \
  (ANTHEM_EXECUTABLE_TYPE) is ${ANTHEM_EXECUTABLE_TYPE} and thus invalid – \
  please set it to either 'anthem' or 'test'")
endif()
