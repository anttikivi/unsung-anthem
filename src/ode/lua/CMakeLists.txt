# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/script.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/stack.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/state.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
