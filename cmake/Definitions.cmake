# Copyright (c) 2017–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(ADD_VERSION_DEFINITIONS)
  add_definitions(-DODE_VERSION="${COMPOSER_ODE_VERSION}")
  add_definitions(-DANTHEM_VERSION="${COMPOSER_ANTHEM_VERSION}")
endfunction()

function(ADD_OPENGL_DEFINITIONS)
  add_definitions(-DODE_OPENGL_VERSION_MAJOR=${COMPOSER_OPENGL_VERSION_MAJOR})
  add_definitions(-DODE_OPENGL_VERSION_MINOR=${COMPOSER_OPENGL_VERSION_MINOR})
endfunction()

function(ADD_DIRECTORY_DEFINITIONS)
  if(WIN32)
    add_definitions(-DODE_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}\\\\ode")
    add_definitions(-DODE_TEST_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}\\\\ode")
    add_definitions(-DANTHEM_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}\\\\anthem")
    add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}\\\\anthem")
  else()
    add_definitions(-DODE_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}/ode")
    add_definitions(-DODE_TEST_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}/ode")
    add_definitions(-DANTHEM_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}/anthem")
    add_definitions(-DANTHEM_TEST_SCRIPT_ROOT="${SCRIPTS_DIRECTORY}/anthem")
  endif()
endfunction()

function(ADD_FEATURE_DEFINITIONS)
  add_definitions(-DGSL_THROW_ON_CONTRACT_VIOLATION=1)
  # add_definitions(-DGSL_UNENFORCED_ON_CONTRACT_VIOLATION=1)

  if(DEVELOPER_BUILD)
    add_definitions(-DODE_DEVELOPER=1)
  else()
    add_definitions(-DODE_DEVELOPER=0)
  endif()

  if(COMPOSER_BUILD_BENCHMARK)
    add_definitions(-DODE_BUILD_BENCHMARK=1)
  else()
    add_definitions(-DODE_BUILD_BENCHMARK=0)
  endif()

  if(STD_CLOCK)
    add_definitions(-DODE_STD_CLOCK=1)
  else()
    add_definitions(-DODE_STD_CLOCK=0)
  endif()

  if(PRINT_LOOP_NANOSECONDS)
    add_definitions(-DODE_PRINT_LOOP_NANOSECONDS=1)
  else()
    add_definitions(-DODE_PRINT_LOOP_NANOSECONDS=0)
  endif()

  if(NULL_TEST_SINK)
    add_definitions(-DODE_NULL_TEST_SINK=1)
  else()
    add_definitions(-DODE_NULL_TEST_SINK=0)
  endif()

  if(MULTITHREADING)
    # add_definitions(-DODE_MULTITHREADING=1)
    add_definitions(-DODE_MULTITHREADING=0)
    message(STATUS "Please note that multithreading is not currently supported")
  else()
    add_definitions(-DODE_MULTITHREADING=0)
  endif()

  if(DISABLE_GL_CALLS)
    add_definitions(-DODE_DISABLE_GL_CALLS=1)
  else()
    add_definitions(-DODE_DISABLE_GL_CALLS=0)
  endif()
endfunction()
