#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved

list(APPEND ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/map_loading.cpp)
list(APPEND ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/world_configuration.cpp)

list(APPEND ANTHEM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/map_loading.h)
list(APPEND ANTHEM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/world_configuration.h)

set(ANTHEM_SOURCES ${ANTHEM_SOURCES} PARENT_SCOPE)
set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES} PARENT_SCOPE)
