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
add_subdirectory(gsl)
add_subdirectory(ode)

set(ODE_LIB_INCLUDES ${ODE_LIB_INCLUDES} PARENT_SCOPE)
set(ANTHEM_LIB_INCLUDES ${ANTHEM_LIB_INCLUDES} PARENT_SCOPE)
