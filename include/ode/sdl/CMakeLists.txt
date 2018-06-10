#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/initialize_sdl.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/opengl.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/sdl_version.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/window_t.h)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
