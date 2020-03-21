# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/environment_manager.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/framework_scene.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/platform_manager.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
