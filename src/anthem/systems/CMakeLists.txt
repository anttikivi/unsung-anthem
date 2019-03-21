#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(input)
add_subdirectory(scenes)

set(ANTHEM_SOURCES ${ANTHEM_SOURCES} PARENT_SCOPE)
set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES} PARENT_SCOPE)
