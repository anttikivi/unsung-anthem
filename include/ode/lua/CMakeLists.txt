#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/lua_config.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/script.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/stack.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/state.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/state_t.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/virtual_machine.h)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
