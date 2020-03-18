#===------------------------ ExternalSources.cmake -------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2019 Antti Kivi
# All rights reserved

function(SET_GLAD_SOURCES)

  list(APPEND ODE_SOURCES ${ODE_DEPENDENCY_PREFIX}/src/glad.c)
  set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)

endfunction()
