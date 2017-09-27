#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

set(ANTHEM_SOURCES ${ANTHEM_SOURCES}

    ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool.cpp

    PARENT_SCOPE)

set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES}

    ${CMAKE_CURRENT_SOURCE_DIR}/task_queue.h
    ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool.h

    PARENT_SCOPE)
