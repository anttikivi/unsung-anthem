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
  add_definitions(-DANTHEM_INPUT_LOGGER_NAME="${ANTHEM_INPUT_LOGGER_NAME}")
  add_definitions(-DANTHEM_WINDOW_NAME="${ANTHEM_WINDOW_NAME}")
  add_definitions(-DANTHEM_OPENGL_VERSION_MAJOR=${ANTHEM_OPENGL_VERSION_MAJOR})
  add_definitions(-DANTHEM_OPENGL_VERSION_MINOR=${ANTHEM_OPENGL_VERSION_MINOR})

  add_definitions(-DGLFW_INCLUDE_NONE)

  if(ANTHEM_MULTITHREADING)
    add_definitions(-DANTHEM_MULTITHREADING=1)
  else()
    add_definitions(-DANTHEM_MULTITHREADING=0)
  endif()
endfunction()
