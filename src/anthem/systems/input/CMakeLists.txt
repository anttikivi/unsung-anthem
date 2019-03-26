#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

list(APPEND ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/input_scene.cpp)
list(APPEND ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/input_system.cpp)

list(APPEND ANTHEM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/input_scene.h)
list(APPEND ANTHEM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/input_system.h)

set(ANTHEM_SOURCES ${ANTHEM_SOURCES} PARENT_SCOPE)
set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES} PARENT_SCOPE)
