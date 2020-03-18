#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved

add_subdirectory(scenes)

set(ANTHEM_TEST_SOURCES ${ANTHEM_TEST_SOURCES} PARENT_SCOPE)
set(ANTHEM_BENCHMARK_SOURCES ${ANTHEM_TEST_SOURCES} PARENT_SCOPE)
