#===---------------------------- Install.cmake -----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(ANTHEM_INSTALLATION)
  install(TARGETS ${ANTHEM_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(ODE_INSTALLATION)
  install(TARGETS ${ODE_NAME} ${ODE_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/private
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(ANTHEM_LIB_INSTALLATION)
  install(TARGETS ${ANTHEM_LIB_NAME} ${ANTHEM_LIB_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include
      PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/include/private
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(ODE_TEST_INSTALLATION)
  install(TARGETS ${ODE_TEST_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endfunction()

function(ANTHEM_TEST_INSTALLATION)
  install(TARGETS ${ANTHEM_TEST_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endfunction()

function(ADD_ODE_INSTALLATION_TARGET TYPE)
  if(${TYPE} STREQUAL lib)
    ode_installation()
  elseif(${TYPE} STREQUAL test)
    ode_test_installation()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ODE_TYPE) is ${ODE_TYPE} and thus \
invalid – please set it to either 'lib' or 'test'")
  endif()
endfunction()

function(ADD_ANTHEM_INSTALLATION_TARGET TYPE)
  if(${TYPE} STREQUAL exe)
    anthem_installation()
  elseif(${TYPE} STREQUAL lib)
    anthem_lib_installation()
  elseif(${TYPE} STREQUAL test)
    anthem_test_installation()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ANTHEM_TYPE) is ${ANTHEM_TYPE} and \
thus invalid – please set it to either 'exe', 'lib', or 'test'")
  endif()
endfunction()
