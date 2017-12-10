#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

set(ANTHEM_SOURCES ${ANTHEM_SOURCES}

    ${CMAKE_CURRENT_SOURCE_DIR}/game_loop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/scheduler.cpp

    PARENT_SCOPE)

set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES}

    ${CMAKE_CURRENT_SOURCE_DIR}/game_loop.h
    ${CMAKE_CURRENT_SOURCE_DIR}/scheduler.h

    PARENT_SCOPE)
