#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(scenes)

set(ANTHEM_TEST_SOURCES ${ANTHEM_TEST_SOURCES} PARENT_SCOPE)
set(ANTHEM_BENCHMARK_SOURCES ${ANTHEM_TEST_SOURCES} PARENT_SCOPE)
