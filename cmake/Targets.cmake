# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(CREATE_ANTHEM_EXECUTABLE_TARGET)
  message(STATUS "Creating target '${COMPOSER_ANTHEM_TARGET}'")
  add_executable(${COMPOSER_ANTHEM_TARGET}
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_SOURCES})
  target_link_libraries(${COMPOSER_ANTHEM_TARGET} ${ODE_LIBRARIES})

  if(DEFINED ODE_MSVC_RUNTIME_LIBRARY)
    set_property(TARGET ${COMPOSER_ANTHEM_TARGET} PROPERTY
        MSVC_RUNTIME_LIBRARY "${ODE_MSVC_RUNTIME_LIBRARY}")
  endif()
endfunction()

function(CREATE_ANTHEM_TEST_EXECUTABLE_TARGET)
  list(REMOVE_ITEM ODE_TEST_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/test/ode/main.cpp)
  list(REMOVE_ITEM ANTHEM_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/src/anthem/main.cpp)
  message(STATUS "Creating target '${COMPOSER_ANTHEM_TEST_TARGET}'")
  if(COMPOSER_BUILD_BENCHMARK)
    add_executable(${COMPOSER_ANTHEM_TEST_TARGET}
        ${ODE_LIB_INCLUDES}
        ${ODE_INCLUDES}
        ${ODE_TEST_INCLUDES}
        ${ODE_TEST_SOURCES}
        ${ODE_BENCHMARK_SOURCES}
        ${ODE_SOURCES}
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_BENCHMARK_SOURCES}
        ${ANTHEM_SOURCES})
  else()
    add_executable(${COMPOSER_ANTHEM_TEST_TARGET}
        ${ODE_LIB_INCLUDES}
        ${ODE_INCLUDES}
        ${ODE_TEST_INCLUDES}
        ${ODE_TEST_SOURCES}
        ${ODE_SOURCES}
        ${ANTHEM_LIB_INCLUDES}
        ${ANTHEM_INCLUDES}
        ${ANTHEM_LIB_SOURCES}
        ${ANTHEM_TEST_SOURCES}
        ${ANTHEM_SOURCES})
  endif()
  target_link_libraries(${COMPOSER_ANTHEM_TEST_TARGET} ${ODE_LIBRARIES})

  if(DEFINED ODE_MSVC_RUNTIME_LIBRARY)
    set_property(TARGET ${COMPOSER_ANTHEM_TEST_TARGET} PROPERTY
        MSVC_RUNTIME_LIBRARY "${ODE_MSVC_RUNTIME_LIBRARY}")
  endif()
endfunction()

function(CREATE_COVERAGE_TARGETS)
  message(STATUS "Going to create the code coverage target")

  append_coverage_compiler_flags()

  set(COVERAGE_EXCLUDES
      ${ODE_DEPENDENCY_PREFIX}/*
      /usr/*
      /Applications/Xcode.app/*)

  setup_target_for_coverage_lcov(NAME ${ANTHEM_NAME}_coverage
      EXECUTABLE ${ANTHEM_TEST_NAME}
      DEPENDECIES ${ANTHEM_TEST_NAME})
endfunction()

function(CREATE_TARGETS)
  # if(ODE_BUILD_STATIC)
  #   create_ode_static_lib_target()
  # endif()
  # if(ODE_BUILD_SHARED)
  #   create_ode_shared_lib_target()
  # endif()
  create_anthem_executable_target()
  # if(ANTHEM_BUILD_STATIC)
  #   create_anthem_static_lib_target()
  # endif()
  # if(ANTHEM_BUILD_SHARED)
  #   create_anthem_shared_lib_target()
  # endif()
  if(COMPOSER_BUILD_TEST)
    create_anthem_test_executable_target()
  endif()
  if(COMPOSER_CODE_COVERAGE)
    include(CodeCoverage)
    create_coverage_targets()
  endif()
endfunction()
