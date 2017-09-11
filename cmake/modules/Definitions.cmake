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
endfunction()
