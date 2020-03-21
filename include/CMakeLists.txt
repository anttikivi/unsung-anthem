# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

add_subdirectory(anthem)
add_subdirectory(gsl)
add_subdirectory(ode)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
set(ANTHEM_LIB_INCLUDES ${ANTHEM_LIB_INCLUDES} PARENT_SCOPE)
