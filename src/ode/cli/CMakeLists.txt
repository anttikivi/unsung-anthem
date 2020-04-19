# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/arguments.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/inclusive_option_group.cpp)
list(APPEND ODE_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/mutually_exclusive_option_group.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/option_group_t.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/option_type.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/option.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/parse_arguments.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
set(ODE_INCLUDES ${ODE_INCLUDES} PARENT_SCOPE)
