#===------------------------- CMakeLists.txt -------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2017 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

add_subdirectory(anthem)
add_subdirectory(gsl)

set(ANTHEM_LIB_INCLUDES ${ANTHEM_LIB_INCLUDES} PARENT_SCOPE)
