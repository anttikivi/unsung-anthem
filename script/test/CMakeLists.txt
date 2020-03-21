# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

add_subdirectory(anthem)
add_subdirectory(ode)

set(ODE_TEST_SCRIPTS ${ODE_TEST_SCRIPTS} PARENT_SCOPE)
set(ANTHEM_TEST_SCRIPTS ${ANTHEM_TEST_SCRIPTS} PARENT_SCOPE)
