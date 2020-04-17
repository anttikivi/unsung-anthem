# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(SET_CXX_DEFINITIONS STD_VERSION)

  if(${STD_VERSION} STREQUAL c++20)

    add_definitions(-DODE_CXX2A=1)
    add_definitions(-DODE_CXX17=0)

  elseif(${STD_VERSION} STREQUAL c++2a)

    add_definitions(-DODE_CXX2A=0)
    add_definitions(-DODE_CXX17=1)

  elseif(${STD_VERSION} STREQUAL c++17)

    add_definitions(-DODE_CXX2A=0)
    add_definitions(-DODE_CXX17=1)

  else()

    message(FATAL_ERROR
        "The C++ standard version (ODE_CXX_VERSION) is set to \
${ODE_CXX_VERSION} and, thus, it is invalid – the possible values are \
c++2a and c++17")

  endif()

  set(ODE_STD ${STD_VERSION} PARENT_SCOPE)

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
