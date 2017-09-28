#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(anthem)
add_subdirectory(gsl)
add_subdirectory(thread)

set(ANTHEM_TEST_SOURCES ${ANTHEM_TEST_SOURCES}

    ${CMAKE_CURRENT_SOURCE_DIR}/arguments_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main_test.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/schedule_test.cpp

    PARENT_SCOPE)
