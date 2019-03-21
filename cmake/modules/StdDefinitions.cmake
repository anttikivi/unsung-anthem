#===------------------------- StdDefinitions.cmake -------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# Licensed under GNU Affero General Public License v3.0

function(SET_CXX2A)
  add_definitions(-DODE_CXX2A=1)
  add_definitions(-DODE_CXX17=0)
  add_definitions(-DANTHEM_CXX2A=1)
  add_definitions(-DANTHEM_CXX17=0)
endfunction()

function(SET_CXX17)
  add_definitions(-DODE_CXX2A=0)
  add_definitions(-DODE_CXX17=1)
  add_definitions(-DANTHEM_CXX2A=0)
  add_definitions(-DANTHEM_CXX17=1)
endfunction()

function(SET_SIMPLE_STD STD_VERSION)
  if(${STD_VERSION} STREQUAL c++2a)
    set(ODE_STD c++17 PARENT_SCOPE)
    set(ANTHEM_STD c++17 PARENT_SCOPE)
  else()
    set(ODE_STD ${STD_VERSION} PARENT_SCOPE)
    set(ANTHEM_STD ${STD_VERSION} PARENT_SCOPE)
  endif()
endfunction()

function(SET_MSBUILD_STD STD_VERSION)
  if(${STD_VERSION} STREQUAL c++2a)
    set(ODE_STD c++latest PARENT_SCOPE)
    set(ANTHEM_STD c++latest PARENT_SCOPE)
  else()
    set_simple_std(${STD_VERSION})
    set(ODE_STD ${ODE_STD} PARENT_SCOPE)
    set(ANTHEM_STD ${ANTHEM_STD} PARENT_SCOPE)
  endif()
endfunction()

function(SET_COMPILER_STD STD_VERSION)
  if(WIN32)
    set_msbuild_std(${STD_VERSION})
  else()
    set_simple_std(${STD_VERSION})
  endif()
  set(ODE_STD ${ODE_STD} PARENT_SCOPE)
  set(ANTHEM_STD ${ANTHEM_STD} PARENT_SCOPE)
endfunction()

function(SET_CXX_DEFINITIONS STD_VERSION)

  if(${STD_VERSION} STREQUAL c++2a)
    set_cxx2a()
  elseif(${STD_VERSION} STREQUAL c++17)
    set_cxx17()
  else()
    message(FATAL_ERROR
        "The C++ standard version (ODE_CXX_VERSION) is set to \
${ODE_CXX_VERSION} and, thus, it is invalid – the possible values are \
c++2a and c++17")
  endif()

  set_compiler_std(${STD_VERSION})
  set(ODE_STD ${ODE_STD} PARENT_SCOPE)
  set(ANTHEM_STD ${ANTHEM_STD} PARENT_SCOPE)
endfunction()

function(SET_STD_FEATURE_DEFINITIONS STD_VERSION)
  if(WIN32)
    add_definitions(-DODE_NO_BRACED_INIT_LIST=1)
    add_definitions(-DANTHEM_NO_BRACED_INIT_LIST=1)
  else()
    add_definitions(-DODE_NO_BRACED_INIT_LIST=0)
    add_definitions(-DANTHEM_NO_BRACED_INIT_LIST=0)
  endif()
endfunction()
