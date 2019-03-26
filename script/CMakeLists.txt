#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

add_subdirectory(anthem)
add_subdirectory(ode)
add_subdirectory(test)

set(ODE_TEST_SCRIPTS ${ODE_TEST_SCRIPTS} PARENT_SCOPE)
set(ODE_SCRIPTS ${ODE_SCRIPTS} PARENT_SCOPE)
set(ANTHEM_LIB_SCRIPTS ${ANTHEM_LIB_SCRIPTS} PARENT_SCOPE)
set(ANTHEM_TEST_SCRIPTS ${ANTHEM_TEST_SCRIPTS} PARENT_SCOPE)
set(ANTHEM_SCRIPTS ${ANTHEM_SCRIPTS} PARENT_SCOPE)
