#===-------------------------- Definitions.cmake ---------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(ADD_NAME_DEFINITIONS)
  add_definitions(-DODE_LOGGER_NAME="${ODE_LOGGER_NAME}")
  add_definitions(-DANTHEM_LOGGER_NAME="${ANTHEM_LOGGER_NAME}")
  add_definitions(-DANTHEM_WINDOW_NAME="${ANTHEM_WINDOW_NAME}")
endfunction()

function(ADD_OPENGL_DEFINITIONS)
  add_definitions(-DODE_OPENGL_VERSION_MAJOR=${ODE_OPENGL_VERSION_MAJOR})
  add_definitions(-DODE_OPENGL_VERSION_MINOR=${ODE_OPENGL_VERSION_MINOR})
  add_definitions(-DGLFW_INCLUDE_NONE)
endfunction()

function(ADD_FEATURE_DEFINITIONS)
  if(ODE_DEVELOPER)
    add_definitions(-DODE_DEVELOPER=1)
    add_definitions(-DODE_TEST_BENCHMARKING=1)
  else()
    add_definitions(-DODE_DEVELOPER=0)
    add_definitions(-DODE_TEST_BENCHMARKING=0)
  endif()

  if(ANTHEM_DEVELOPER)
    add_definitions(-DANTHEM_DEVELOPER=1)
    add_definitions(-DANTHEM_TEST_BENCHMARKING=1)
  else()
    add_definitions(-DANTHEM_DEVELOPER=0)
    add_definitions(-DANTHEM_TEST_BENCHMARKING=1)
  endif()

  if(ODE_MULTITHREADING)
    add_definitions(-DODE_MULTITHREADING=1)
    add_definitions(-DANTHEM_MULTITHREADING=1)
  else()
    add_definitions(-DODE_MULTITHREADING=0)
    add_definitions(-DANTHEM_MULTITHREADING=0)
  endif()
endfunction()

function(ADD_DIRECTORY_DEFINITIONS)
  if(ODE_ENABLE_GCOV)
    add_definitions(-DODE_SCRIPT_ROOT="${ODE_SCRIPT_DIR_NAME}/ode")
    add_definitions(-DODE_TEST_SCRIPT_ROOT="${ODE_TEST_SCRIPT_DIR_NAME}/ode")
    add_definitions(-DANTHEM_SCRIPT_ROOT="${ODE_SCRIPT_DIR_NAME}/anthem")
    add_definitions(-DANTHEM_LIB_SCRIPT_ROOT="${ODE_LIB_SCRIPT_DIR_NAME}/anthem")
    add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="${ODE_TEST_SCRIPT_DIR_NAME}/anthem")
  else()
    add_definitions(-DODE_SCRIPT_ROOT="../${ODE_SCRIPT_DIR_NAME}/ode")
    add_definitions(-DODE_TEST_SCRIPT_ROOT="../${ODE_TEST_SCRIPT_DIR_NAME}/ode")
    add_definitions(-DANTHEM_SCRIPT_ROOT="../${ODE_SCRIPT_DIR_NAME}/anthem")
    add_definitions(-DANTHEM_LIB_SCRIPT_ROOT="../${ODE_LIB_SCRIPT_DIR_NAME}/anthem")
    add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="../${ODE_TEST_SCRIPT_DIR_NAME}/anthem")
  endif()
endfunction()
