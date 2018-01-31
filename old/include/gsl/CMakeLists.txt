#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

set(ANTHEM_LIB_INCLUDES ${ANTHEM_LIB_INCLUDES}

    ${CMAKE_CURRENT_SOURCE_DIR}/assert
    ${CMAKE_CURRENT_SOURCE_DIR}/util
    ${CMAKE_CURRENT_SOURCE_DIR}/view

    PARENT_SCOPE)
