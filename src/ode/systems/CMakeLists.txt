# Copyright (c) 2018–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

add_subdirectory(graphics)
add_subdirectory(input)

list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/scene_configuration.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/system_t.cpp)
list(APPEND ODE_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/system_type.cpp)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
