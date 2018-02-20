#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(lua)

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/command_line_interface.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/execute.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp)

list(APPEND ODE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logging_config.h)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
set(ODE_INCLUDES ${ODE_INCLUDES} PARENT_SCOPE)
