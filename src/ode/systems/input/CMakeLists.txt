#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/input_system.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
