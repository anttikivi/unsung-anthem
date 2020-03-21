# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/data.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/gl_config.h)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
