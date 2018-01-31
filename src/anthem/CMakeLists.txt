#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
list(APPEND ANTHEM_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/run.cpp)

list(APPEND ANTHEM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/logging_config.h)
list(APPEND ANTHEM_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/run.h)

set(ANTHEM_SOURCES ${ANTHEM_SOURCES} PARENT_SCOPE)
set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES} PARENT_SCOPE)
