#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/notification_queue.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/thread_pool.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
set(ODE_INCLUDES ${ODE_INCLUDES} PARENT_SCOPE)
