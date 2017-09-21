#===---------------------- CompilerFlags.cmake -----------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(SET_STD_FLAGS STD)

  if (${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL msbuild)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:${STD}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${STD}")
  endif()

  if (DEFINED ANTHEM_STDLIB
      AND NOT ${ANTHEM_MAIN_COMPILER_TOOL} STREQUAL msbuild)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=${ANTHEM_STDLIB}")
  endif()

  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
endfunction()
