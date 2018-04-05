#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(filesystem)
add_subdirectory(lua)
add_subdirectory(sdl)

list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/__config)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/argv_array.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/execution_info.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/initialize.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logger.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logging.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/main_loop.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/pixel_count.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/quit.h)
list(APPEND ODE_LIB_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/window_t.h)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
