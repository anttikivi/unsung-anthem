#===------------------------- Install.cmake --------------------------------===#
#
#                             Unsung Anthem
#
# This source file is part of the Unsung Anthem open source project.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(MAIN_INSTALLATION)
  install(TARGETS
      ${ANTHEM_EXECUTABLE_NAME}
      ${ANTHEM_LIB_NAME}
      ${ANTHEM_LIB_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(TEST_INSTALLATION)
  install(
      TARGETS ${ANTHEM_TEST_EXECUTABLE_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endfunction()

function(ADD_INSTALLATION_TARGET TYPE)
  if(${TYPE} STREQUAL anthem)
    main_installation()
  elseif(${TYPE} STREQUAL test)
    test_installation()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ANTHEM_EXECUTABLE_TYPE) is \
${ANTHEM_EXECUTABLE_TYPE} and thus invalid – please set it to either \
'anthem' or 'test'")
  endif()
endfunction()
