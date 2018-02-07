#===---------------------------- CMakeLists.txt ----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(anthem)
add_subdirectory(ode)

set(ODE_TEST_SCRIPTS ${ODE_TEST_SCRIPTS} PARENT_SCOPE)
set(ANTHEM_TEST_SCRIPTS ${ANTHEM_TEST_SCRIPTS} PARENT_SCOPE)
