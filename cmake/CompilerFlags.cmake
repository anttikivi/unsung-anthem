# Copyright (c) 2017–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(SET_STD_FLAGS STD)

  if (${STD} STREQUAL c++20)
    set(STD_FLAG c++2a)
  else()
    set(STD_FLAG ${STD})
  endif()

  if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:${STD_FLAG}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${STD_FLAG}")
  endif()

  if (DEFINED ODE_STDLIB AND NOT WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=${ODE_STDLIB} -nostdinc++")
  endif()

  set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} PARENT_SCOPE)
endfunction()

function(SET_LINKER_FLAGS)
  if(DEFINED ODE_RPATH)
    if(APPLE)
      set(CMAKE_EXE_LINKER_FLAGS
          "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${ODE_RPATH}")
    else()
      set(CMAKE_EXE_LINKER_FLAGS
          "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'${ODE_RPATH}'")
    endif()
  endif()
  set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} PARENT_SCOPE)
endfunction()
