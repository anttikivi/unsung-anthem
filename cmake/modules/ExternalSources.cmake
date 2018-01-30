#===--------------------- ExternalSources.cmake ----------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(SET_GLAD_SOURCES)

  set(ODE_SOURCES ${ODE_SOURCES}

      ${ODE_INSTALL_PREFIX}/src/glad.c

      PARENT_SCOPE)

endfunction()
