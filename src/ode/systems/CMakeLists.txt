#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

add_subdirectory(graphics)
add_subdirectory(input)

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/scene_configuration.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/system_t.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/system_type.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
