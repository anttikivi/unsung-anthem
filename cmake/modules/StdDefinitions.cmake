#===---------------------- StdDefinitions.cmake ----------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(SET_CXX2A)
  add_definitions(-DANTHEM_CXX2A=1)
  add_definitions(-DANTHEM_CXX17=0)
  add_definitions(-DANTHEM_CXX14=0)
endfunction()

function(SET_CXX17)
  add_definitions(-DANTHEM_CXX2A=0)
  add_definitions(-DANTHEM_CXX17=1)
  add_definitions(-DANTHEM_CXX14=0)
endfunction()

function(SET_CXX14)
  add_definitions(-DANTHEM_CXX2A=0)
  add_definitions(-DANTHEM_CXX17=0)
  add_definitions(-DANTHEM_CXX14=1)
endfunction()

function(SET_SIMPLE_STD STD_VERSION)
  if(${STD_VERSION} STREQUAL c++2a)
    set(ANTHEM_STD c++17 PARENT_SCOPE)
  else()
    set(ANTHEM_STD ${STD_VERSION} PARENT_SCOPE)
  endif()
endfunction()

function(SET_MSBUILD_STD STD_VERSION)
  if(${STD_VERSION} STREQUAL c++latest)
    set(ANTHEM_STD c++latest PARENT_SCOPE)
  else()
    set_simple_std(${STD_VERSION})
    set(ANTHEM_STD ${ANTHEM_STD} PARENT_SCOPE)
  endif()
endfunction()

function(SET_LLVM_STD STD_VERSION)
  if(${STD_VERSION} STREQUAL c++14)
    set(ANTHEM_STD ${STD_VERSION} PARENT_SCOPE)
  else()
    set(ANTHEM_STD c++1z PARENT_SCOPE)
  endif()
endfunction()

function(SET_COMPILER_STD COMPILER_TOOL STD_VERSION)
  if(${COMPILER_TOOL} STREQUAL msbuild)
    set_msbuild_std(${STD_VERSION})
  elseif(${COMPILER_TOOL} STREQUAL gcc)
    set_simple_std(${STD_VERSION})
  elseif(${COMPILER_TOOL} STREQUAL llvm)
    set_llvm_std(${STD_VERSION})
  endif()
  set(ANTHEM_STD ${ANTHEM_STD} PARENT_SCOPE)
endfunction()

function(SET_CXX_DEFINITIONS STD_VERSION)

  if(${STD_VERSION} STREQUAL c++latest)
    set_cxx17()
  elseif(${STD_VERSION} STREQUAL c++2a)
    set_cxx2a()
  elseif(${STD_VERSION} STREQUAL c++17)
    set_cxx17()
  elseif(${STD_VERSION} STREQUAL c++14)
    set_cxx14()
  else()
    message(FATAL_ERROR
        "The C++ standard version (ANTHEM_CXX_VERSION) is set to \
${ANTHEM_CXX_VERSION} and, thus, it is invalid – the possible values are \
c++2a, c++17, c++14, and c++latest")
  endif()

  set_compiler_std(${ANTHEM_MAIN_COMPILER_TOOL} ${STD_VERSION})
  set(ANTHEM_STD ${ANTHEM_STD} PARENT_SCOPE)
endfunction()

function(SET_STD_FEATURE_DEFINITIONS STD_VERSION)
  if(${STD_VERSION} STREQUAL c++14)
    add_definitions(-DANTHEM_INLINE_VARIABLES=0)
  else()
    add_definitions(-DANTHEM_INLINE_VARIABLES=1)
  endif()
endfunction()
