#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(framework)
add_subdirectory(manager)
add_subdirectory(system)
add_subdirectory(thread)

set(ANTHEM_SOURCES ${ANTHEM_SOURCES}

    ${CMAKE_CURRENT_SOURCE_DIR}/arguments.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/execute.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/sdl.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/window.cpp

    PARENT_SCOPE)

set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES}

    ${CMAKE_CURRENT_SOURCE_DIR}/args_array.h
    ${CMAKE_CURRENT_SOURCE_DIR}/arguments.h
    ${CMAKE_CURRENT_SOURCE_DIR}/execute.h
    ${CMAKE_CURRENT_SOURCE_DIR}/logging_config.h
    ${CMAKE_CURRENT_SOURCE_DIR}/sdl.h
    ${CMAKE_CURRENT_SOURCE_DIR}/window.h

    PARENT_SCOPE)
