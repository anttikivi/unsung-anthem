# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(CREATE_ODE_STATIC_LIB)
  message(STATUS "Creating target '${ODE_NAME}'")
  add_library(${ODE_NAME} STATIC
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES})
  target_link_libraries(${ODE_NAME} ${ODE_LIBRARIES})

  set_target_properties(${ODE_NAME} PROPERTIES
      PUBLIC_HEADER "${ODE_LIB_INCLUDES}")
  set_target_properties(${ODE_NAME} PROPERTIES
      PRIVATE_HEADER "${ODE_INCLUDES}")
endfunction()

function(CREATE_ODE_SHARED_LIB)
  message(STATUS "Creating target '${ODE_NAME}${ODE_DYNAMIC_MARK}'")
  add_library(${ODE_NAME}${ODE_DYNAMIC_MARK} SHARED
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES})
  target_link_libraries(${ODE_NAME}${ODE_DYNAMIC_MARK} ${ODE_LIBRARIES})

  set_target_properties(${ODE_NAME}${ODE_DYNAMIC_MARK} PROPERTIES
      PUBLIC_HEADER "${ODE_LIB_INCLUDES}")
  set_target_properties(${ODE_NAME}${ODE_DYNAMIC_MARK} PROPERTIES
      PRIVATE_HEADER "${ODE_INCLUDES}")

  if(UNIX)
    set_target_properties(${ODE_NAME}${ODE_DYNAMIC_MARK} PROPERTIES
        OUTPUT_NAME ${ODE_NAME})
  endif()
endfunction()

function(CREATE_ANTHEM_EXECUTABLE)
  message(STATUS "Creating target '${ANTHEM_NAME}'")
  add_executable(${ANTHEM_NAME}
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_INCLUDES}
      ${ANTHEM_LIB_SOURCES}
      ${ANTHEM_SOURCES})
  target_link_libraries(${ANTHEM_NAME} ${ODE_LIBRARIES})

  if(DEFINED ODE_MSVC_RUNTIME_LIBRARY)
    set_property(TARGET ${ANTHEM_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "${ODE_MSVC_RUNTIME_LIBRARY}")
  endif()
endfunction()

function(CREATE_ANTHEM_STATIC_LIB)
  message(STATUS "Creating target '${ANTHEM_LIB_NAME}'")
  add_library(${ANTHEM_LIB_NAME} STATIC
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_LIB_SOURCES})
  target_link_libraries(${ANTHEM_LIB_NAME} ${ODE_LIBRARIES})

  set_target_properties(${ANTHEM_LIB_NAME} PROPERTIES
      PUBLIC_HEADER "${ANTHEM_LIB_INCLUDES}")
  set_target_properties(${ANTHEM_LIB_NAME} PROPERTIES
      PRIVATE_HEADER "${ANTHEM_INCLUDES}")
endfunction()

function(CREATE_ANTHEM_SHARED_LIB)
  message(STATUS "Creating target '${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK}'")
  add_library(${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK} SHARED
      ${ODE_LIB_INCLUDES}
      ${ODE_INCLUDES}
      ${ODE_SOURCES}
      ${ANTHEM_LIB_INCLUDES}
      ${ANTHEM_LIB_SOURCES})
  target_link_libraries(${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK} ${ODE_LIBRARIES})

  set_target_properties(${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK} PROPERTIES
      PUBLIC_HEADER "${ANTHEM_LIB_INCLUDES}")
  set_target_properties(${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK} PROPERTIES
      PRIVATE_HEADER "${ANTHEM_INCLUDES}")

  if(UNIX)
    set_target_properties(${ANTHEM_LIB_NAME}${ODE_DYNAMIC_MARK} PROPERTIES
        OUTPUT_NAME ${ANTHEM_LIB_NAME})
  endif()
endfunction()

function(CREATE_ANTHEM_TEST_EXECUTABLE)
  list(REMOVE_ITEM ODE_TEST_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/test/ode/main.cpp)
  list(REMOVE_ITEM ANTHEM_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/src/anthem/main.cpp)
  message(STATUS "Creating target '${ANTHEM_TEST_NAME}'")
  if(ODE_TEST_BENCHMARKING)
    add_executable(${ANTHEM_TEST_NAME}
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
    add_executable(${ANTHEM_TEST_NAME}
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
  target_link_libraries(${ANTHEM_TEST_NAME} ${ODE_LIBRARIES})

  if(DEFINED ODE_MSVC_RUNTIME_LIBRARY)
    set_property(TARGET ${ANTHEM_TEST_NAME} PROPERTY
        MSVC_RUNTIME_LIBRARY "${ODE_MSVC_RUNTIME_LIBRARY}")
  endif()
endfunction()

function(CREATE_COVERAGE_TARGETS)
  message(STATUS "Going to create the code coverage target")

  append_coverage_compiler_flags()

  set(COVERAGE_EXCLUDES
      ${ODE_DEPENDENCY_PREFIX}/include/*
      ${ODE_DEPENDENCY_PREFIX}/include/benchmark/*
      ${ODE_DEPENDENCY_PREFIX}/include/glad/*
      ${ODE_DEPENDENCY_PREFIX}/include/GLFW/*
      ${ODE_DEPENDENCY_PREFIX}/include/gtest/*
      ${ODE_DEPENDENCY_PREFIX}/include/gtest/internal/*
      ${ODE_DEPENDENCY_PREFIX}/include/hayai/*
      ${ODE_DEPENDENCY_PREFIX}/include/KHR/*
      ${ODE_DEPENDENCY_PREFIX}/include/SDL2/*
      ${ODE_DEPENDENCY_PREFIX}/include/spdlog/*
      ${ODE_DEPENDENCY_PREFIX}/include/spdlog/details/*
      ${ODE_DEPENDENCY_PREFIX}/include/spdlog/fmt/*
      ${ODE_DEPENDENCY_PREFIX}/include/spdlog/fmt/bundled/*
      ${ODE_DEPENDENCY_PREFIX}/include/spdlog/sinks/*
      ${ODE_DEPENDENCY_PREFIX}/src/*
      ${ODE_DEPENDENCY_PREFIX}/src/benchmark/*
      ${ODE_DEPENDENCY_PREFIX}/src/gtest/src/*
      /usr/include/*
      /usr/include/c++*
      *v1*
      *7*)

  setup_target_for_coverage_lcov(NAME ${ANTHEM_NAME}_coverage
      EXECUTABLE ${ANTHEM_TEST_NAME}
      DEPENDECIES ${ANTHEM_TEST_NAME})
endfunction()

function(CREATE_TARGETS)
  if(ODE_BUILD_STATIC)
    create_ode_static_lib()
  endif()
  if(ODE_BUILD_SHARED)
    create_ode_shared_lib()
  endif()
  create_anthem_executable()
  if(ANTHEM_BUILD_STATIC)
    create_anthem_static_lib()
  endif()
  if(ANTHEM_BUILD_SHARED)
    create_anthem_shared_lib()
  endif()
  if(ODE_BUILD_TEST)
    create_anthem_test_executable()
  endif()
  if(ODE_CODE_COVERAGE)
    include(CodeCoverage)
    create_coverage_targets()
  endif()
endfunction()
