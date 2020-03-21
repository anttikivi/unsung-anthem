# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/option.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/parse_arguments.h)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
