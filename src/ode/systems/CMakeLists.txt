#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/graphics_system.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/input_system.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/scene_configuration.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/system_t.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/system_type.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
