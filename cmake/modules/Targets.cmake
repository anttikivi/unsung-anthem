#===------------------------- Targets.cmake --------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(CREATE_ODE_LIB)
  add_library(${ODE_NAME} STATIC
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES})
  add_library(${ODE_NAME}_shared SHARED
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES})
  target_link_libraries(${ODE_NAME} ${ODE_LIBRARIES})
  target_link_libraries(${ODE_NAME}_shared ${ODE_LIBRARIES})

  if(UNIX)
    set_target_properties(${ODE_NAME}_shared PROPERTIES
        OUTPUT_NAME ${ODE_NAME})
  endif()
endfunction()

function(CREATE_ODE_TEST_EXECUTABLE)
  add_executable(${ODE_TEST_NAME}
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_TEST_SOURCES}
      ${ODE_SOURCES})
  target_link_libraries(${ODE_TEST_NAME} ${ODE_LIBRARIES})
endfunction()

function(CREATE_ANTHEM_EXECUTABLE)
  add_executable(${ANTHEM_NAME}
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_SOURCES})
  target_link_libraries(${ANTHEM_NAME} ${ODE_LIBRARIES} ${ANTHEM_LIBRARIES})
endfunction()

function(CREATE_ANTHEM_LIB)
  add_library(${ANTHEM_LIB_NAME} STATIC
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_LIB_SOURCES})
  add_library(${ANTHEM_LIB_NAME}_shared SHARED
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_LIB_SOURCES})
  target_link_libraries(${ANTHEM_LIB_NAME}
      ${ODE_LIBRARIES}
      ${ANTHEM_LIBRARIES})
  target_link_libraries(${ANTHEM_LIB_NAME}_shared
      ${ODE_LIBRARIES}
      ${ANTHEM_LIBRARIES})

  if(UNIX)
    set_target_properties(${ANTHEM_LIB_NAME}_shared PROPERTIES
        OUTPUT_NAME ${ANTHEM_LIB_NAME})
  endif()
endfunction()

function(CREATE_ANTHEM_TEST_EXECUTABLE)
  list(REMOVE_ITEM ODE_TEST_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/test/ode/main.cpp)
  list(REMOVE_ITEM ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
  add_executable(${ANTHEM_TEST_NAME}
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_TEST_SOURCES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_TEST_SOURCES}
      ${ANTHEM_SOURCES})
  target_link_libraries(${ANTHEM_TEST_NAME}
      ${ODE_LIBRARIES}
      ${ANTHEM_LIBRARIES})
endfunction()

function(SET_UP_COVERAGE TARGET COVERAGE_TARGET)
  message(STATUS "Setting up ${COVERAGE_TARGET} for code coverage")
  include(CodeCoverage)
  set(COVERAGE_EXCLUDES
      ${ODE_INSTALL_PREFIX}/include/*
      ${ODE_INSTALL_PREFIX}/include/glad/*
      ${ODE_INSTALL_PREFIX}/include/GLFW/*
      ${ODE_INSTALL_PREFIX}/include/KHR/*
      ${ODE_INSTALL_PREFIX}/include/SDL2/*
      ${ODE_INSTALL_PREFIX}/include/spdlog/*
      ${ODE_INSTALL_PREFIX}/include/spdlog/details/*
      ${ODE_INSTALL_PREFIX}/include/spdlog/fmt/*
      ${ODE_INSTALL_PREFIX}/include/spdlog/fmt/bundled/*
      ${ODE_INSTALL_PREFIX}/include/spdlog/sinks/*
      ${ODE_INSTALL_PREFIX}/src/*
      /usr/include/*
      /usr/include/c++*
      *v1*
      *7*)
  setup_target_for_coverage(NAME ${TARGET}_coverage
      EXECUTABLE ${COVERAGE_TARGET})
endfunction()

function(CREATE_ODE TYPE)
  if(${TYPE} STREQUAL lib)
    create_ode_lib()
  elseif(${TYPE} STREQUAL test)
    create_ode_test_executable()
    if(ODE_ENABLE_GCOV)
      set_up_coverage(${ODE_NAME} ${ODE_TEST_EXECUTABLE_NAME})
    endif()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ODE_TYPE) is ${ODE_TYPE} and thus \
invalid – please set it to either 'lib' or 'test'")
  endif()
endfunction()

function(CREATE_ANTHEM TYPE)
  if(${TYPE} STREQUAL exe)
    create_anthem_executable()
  elseif(${TYPE} STREQUAL lib)
    create_anthem_lib()
  elseif(${TYPE} STREQUAL test)
    create_anthem_test_executable()
    if(ODE_ENABLE_GCOV)
      set_up_coverage(${ANTHEM_NAME} ${ANTHEM_TEST_NAME})
    endif()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ANTHEM_TYPE) is ${ANTHEM_TYPE} and \
thus invalid – please set it to either 'exe', 'lib', or 'test'")
  endif()
endfunction()
