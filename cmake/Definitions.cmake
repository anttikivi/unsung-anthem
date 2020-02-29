#===-------------------------- Definitions.cmake ---------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

function(ADD_NAME_DEFINITIONS)
  add_definitions(-DODE_LOGGER_NAME="${ODE_LOGGER_NAME}")
  add_definitions(-DODE_WINDOW_NAME="${ODE_WINDOW_NAME}")
  add_definitions(-DANTHEM_LOGGER_NAME="${ANTHEM_LOGGER_NAME}")
  add_definitions(-DANTHEM_WINDOW_NAME="${ANTHEM_WINDOW_NAME}")
endfunction()

function(ADD_VERSION_DEFINITIONS)
  add_definitions(-DODE_VERSION="${ODE_VERSION}")
  add_definitions(-DANTHEM_VERSION="${ANTHEM_VERSION}")
endfunction()

function(ADD_OPENGL_DEFINITIONS)
  add_definitions(-DODE_OPENGL_VERSION_MAJOR=${ODE_OPENGL_VERSION_MAJOR})
  add_definitions(-DODE_OPENGL_VERSION_MINOR=${ODE_OPENGL_VERSION_MINOR})
endfunction()

function(ADD_DIRECTORY_DEFINITIONS)
  # add_definitions(-DODE_SCRIPT_ROOT="${CMAKE_INSTALL_LIBDIR}/ode")
  # add_definitions(-DODE_TEST_SCRIPT_ROOT="${CMAKE_INSTALL_LIBDIR}/ode")
  # add_definitions(-DANTHEM_SCRIPT_ROOT="${CMAKE_INSTALL_LIBDIR}/anthem")
  # add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="${CMAKE_INSTALL_LIBDIR}/anthem")
  if(WIN32)
    add_definitions(-DODE_SCRIPT_ROOT="lib\\ode")
    add_definitions(-DODE_TEST_SCRIPT_ROOT="lib\\ode")
    add_definitions(-DANTHEM_SCRIPT_ROOT="lib\\anthem")
    add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="lib\\anthem")
  else()
    add_definitions(-DODE_SCRIPT_ROOT="lib/ode")
    add_definitions(-DODE_TEST_SCRIPT_ROOT="lib/ode")
    add_definitions(-DANTHEM_SCRIPT_ROOT="lib/anthem")
    add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="lib/anthem")
  endif()
endfunction()

function(ADD_FEATURE_DEFINITIONS)
  add_definitions(-DGSL_THROW_ON_CONTRACT_VIOLATION=1)
  # add_definitions(-DGSL_UNENFORCED_ON_CONTRACT_VIOLATION=1)

  if(ODE_DEVELOPER)
    add_definitions(-DODE_DEVELOPER=1)
  else()
    add_definitions(-DODE_DEVELOPER=0)
  endif()

  if(ODE_TEST_BENCHMARKING)
    add_definitions(-DODE_TEST_BENCHMARKING=1)
  else()
    add_definitions(-DODE_TEST_BENCHMARKING=0)
  endif()

  if(ODE_STD_CLOCK)
    add_definitions(-DODE_STD_CLOCK=1)
  else()
    add_definitions(-DODE_STD_CLOCK=0)
  endif()

  if(ODE_PRINT_LOOP_NANOSECONDS)
    add_definitions(-DODE_PRINT_LOOP_NANOSECONDS=1)
  else()
    add_definitions(-DODE_PRINT_LOOP_NANOSECONDS=0)
  endif()

  if(ODE_TEST_USE_NULL_SINK)
    add_definitions(-DODE_TEST_USE_NULL_SINK=1)
  else()
    add_definitions(-DODE_TEST_USE_NULL_SINK=0)
  endif()

  if(ODE_MULTITHREADING)
    # add_definitions(-DODE_MULTITHREADING=1)
    add_definitions(-DODE_MULTITHREADING=0)
    message(STATUS "Please note that multithreading is not currently supported")
  else()
    add_definitions(-DODE_MULTITHREADING=0)
  endif()

  if(ODE_DISABLE_GL_CALLS)
    add_definitions(-DODE_DISABLE_GL_CALLS=1)
  else()
    add_definitions(-DODE_DISABLE_GL_CALLS=0)
  endif()
endfunction()
