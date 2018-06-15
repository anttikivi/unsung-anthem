#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

list(APPEND ANTHEM_SCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/map.lua)

set(ANTHEM_LIB_SCRIPTS ${ANTHEM_LIB_SCRIPTS} PARENT_SCOPE)
set(ANTHEM_SCRIPTS ${ANTHEM_SCRIPTS} PARENT_SCOPE)
