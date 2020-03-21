# Copyright (c) 2020 Antti Kivi
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
  if(ODE_ENABLE_GCOV)
    set_up_coverage(${ANTHEM_NAME} ${ANTHEM_TEST_NAME})
  endif()
endfunction()
