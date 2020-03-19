#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved

add_subdirectory(cli)
add_subdirectory(framework)
add_subdirectory(gl)
add_subdirectory(lua)
add_subdirectory(sdl)
add_subdirectory(systems)

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/initialize.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/logging.cpp)

list(APPEND ODE_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logging_config.h)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
set(ODE_INCLUDES ${ODE_INCLUDES} PARENT_SCOPE)
