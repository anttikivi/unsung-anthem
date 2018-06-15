#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ANTHEM_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/map_loading_test.cpp)

set(ANTHEM_TEST_SOURCES ${ANTHEM_TEST_SOURCES} PARENT_SCOPE)
