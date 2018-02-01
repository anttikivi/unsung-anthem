#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ANTHEM_LIB_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/logger.cpp)

set(ANTHEM_LIB_SOURCES ${ANTHEM_LIB_SOURCES} PARENT_SCOPE)
