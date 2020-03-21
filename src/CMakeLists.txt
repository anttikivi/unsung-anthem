# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

add_subdirectory(anthem)
add_subdirectory(ode)

set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)
set(ODE_INCLUDES ${ODE_INCLUDES} PARENT_SCOPE)
set(ANTHEM_SOURCES ${ANTHEM_SOURCES} PARENT_SCOPE)
set(ANTHEM_INCLUDES ${ANTHEM_INCLUDES} PARENT_SCOPE)
