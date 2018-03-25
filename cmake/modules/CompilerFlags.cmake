#===-------------------------- CompilerFlags.cmake -------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(SET_STD_FLAGS STD)

  if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:${STD}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${STD}")
    if (ODE_USE_LOCAL_LLVM)
      set(CMAKE_CXX_FLAGS
          "${CMAKE_CXX_FLAGS} -I${ODE_INSTALL_PREFIX}/include/c++/v1")
    endif()
  endif()

  if (DEFINED ODE_STDLIB AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=${ODE_STDLIB}")
  endif()

  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
endfunction()

function(SET_COMPILER_FLAGS)
  if(ODE_SET_RPATH)
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wl,-rpath,${CMAKE_INSTALL_PREFIX}/bin")
  endif()
  if(DEFINED ODE_OPTIMIZATION_LEVEL)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O${ODE_OPTIMIZATION_LEVEL}")
  endif()
  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
endfunction()

