# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(SET_CPP_DEFINITIONS CPP_STD)

  if(${CPP_STD} STREQUAL c++20)

    add_definitions(-DODE_CXX20=1)
    add_definitions(-DODE_CXX17=0)

  elseif(${CPP_STD} STREQUAL c++17)

    add_definitions(-DODE_CXX20=0)
    add_definitions(-DODE_CXX17=1)

  else()

    message(FATAL_ERROR
        "The C++ standard version (COMPOSER_CPP_STD) is set to \
${COMPOSER_CPP_STD} and, thus, it is invalid – the possible values are \
c++20 and c++17")

  endif()

  set(CPP_STD ${CPP_STD} PARENT_SCOPE)

endfunction()

function(SET_CPP_FEATURE_DEFINITIONS)
  if(WIN32)
    add_definitions(-DODE_NO_BRACED_INIT_LIST=1)
    add_definitions(-DANTHEM_NO_BRACED_INIT_LIST=1)
  else()
    add_definitions(-DODE_NO_BRACED_INIT_LIST=0)
    add_definitions(-DANTHEM_NO_BRACED_INIT_LIST=0)
  endif()
endfunction()
