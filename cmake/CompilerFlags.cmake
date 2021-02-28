# Copyright (c) 2017–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(SET_CPP_STD_FLAGS CPP_STD)

  set(CPP_STD_FLAG ${CPP_STD})

  if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:${CPP_STD_FLAG}")
  else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=${CPP_STD_FLAG}")
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

function(SET_COVERAGE_FLAGS)
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage" PARENT_SCOPE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage" PARENT_SCOPE)
endfunction()
