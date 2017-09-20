#===----------------------- Definitions.cmake ------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(ADD_LOGGER_DEFINITIONS)
  add_definitions(-DANTHEM_LOGGER_NAME="${ANTHEM_LOGGER_NAME}")

  if(${ANTHEM_GLFW})
    add_definitions(-DANTHEM_GLFW=1)
    add_definitions(-DANTHEM_SDL=0)
  elseif(${ANTHEM_SDL})
    add_definitions(-DANTHEM_GLFW=0)
    add_definitions(-DANTHEM_SDL=1)
  endif()
endfunction()
