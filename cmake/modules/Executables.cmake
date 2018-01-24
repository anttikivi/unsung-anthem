#===----------------------- Executables.cmake ------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(CREATE_MAIN_EXECUTABLE)
  add_executable(${ANTHEM_EXECUTABLE_NAME}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_SOURCES})
  add_library(${ANTHEM_LIB_NAME} STATIC
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_LIB_SOURCES})
  add_library(${ANTHEM_LIB_NAME}_shared SHARED
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_LIB_SOURCES})
  target_link_libraries(${ANTHEM_EXECUTABLE_NAME} ${ANTHEM_LIBRARIES})
  target_link_libraries(${ANTHEM_LIB_NAME} ${ANTHEM_LIBRARIES})
  target_link_libraries(${ANTHEM_LIB_NAME}_shared ${ANTHEM_LIBRARIES})

  if(UNIX)
    set_target_properties(${ANTHEM_LIB_NAME}_shared PROPERTIES
        OUTPUT_NAME ${ANTHEM_LIB_NAME})
  endif()
endfunction()

function(CREATE_TEST_EXECUTABLE)
  list(REMOVE_ITEM ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
  add_executable(${ANTHEM_TEST_EXECUTABLE_NAME}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_TEST_SOURCES}
      ${ANTHEM_SOURCES})
  target_link_libraries(${ANTHEM_TEST_EXECUTABLE_NAME} ${ANTHEM_LIBRARIES})
endfunction()

function(SET_UP_COVERAGE COVERAGE_TARGET)
  message(STATUS "Setting up ${COVERAGE_TARGET} for code coverage")
  include(CodeCoverage)
  set(COVERAGE_EXCLUDES
      ${ANTHEM_INSTALL_PREFIX}/include/*
      ${ANTHEM_INSTALL_PREFIX}/include/glad/*
      ${ANTHEM_INSTALL_PREFIX}/include/GLFW/*
      ${ANTHEM_INSTALL_PREFIX}/include/KHR/*
      ${ANTHEM_INSTALL_PREFIX}/include/SDL2/*
      ${ANTHEM_INSTALL_PREFIX}/include/spdlog/*
      ${ANTHEM_INSTALL_PREFIX}/include/spdlog/details/*
      ${ANTHEM_INSTALL_PREFIX}/include/spdlog/fmt/*
      ${ANTHEM_INSTALL_PREFIX}/include/spdlog/fmt/bundled/*
      ${ANTHEM_INSTALL_PREFIX}/include/spdlog/sinks/*
      ${ANTHEM_INSTALL_PREFIX}/src/*
      /usr/include/*
      /usr/include/c++*
      *v1*
      *7*)
  setup_target_for_coverage(NAME ${ANTHEM_EXECUTABLE_NAME}_coverage
      EXECUTABLE ${COVERAGE_TARGET})
endfunction()

function(CREATE_EXECUTABLE TYPE)
  if(${TYPE} STREQUAL anthem)
    create_main_executable()
  elseif(${TYPE} STREQUAL test)
    create_test_executable()
    if (ANTHEM_ENABLE_GCOV)
      set_up_coverage(${ANTHEM_TEST_EXECUTABLE_NAME})
    endif()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ANTHEM_EXECUTABLE_TYPE) is \
${ANTHEM_EXECUTABLE_TYPE} and thus invalid – please set it to either \
'anthem' or 'test'")
  endif()
endfunction()
