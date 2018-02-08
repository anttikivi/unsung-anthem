#===---------------------------- Install.cmake -----------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(ODE_INSTALLATION)
  install(TARGETS ${ODE_NAME} ${ODE_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
      PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME})
endfunction()

function(ODE_TEST_INSTALLATION)
  install(TARGETS ${ODE_TEST_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME})
endfunction()

function(ANTHEM_INSTALLATION)
  install(TARGETS ${ANTHEM_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME}
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME})
endfunction()

function(ANTHEM_LIB_INSTALLATION)
  install(TARGETS ${ANTHEM_LIB_NAME} ${ANTHEM_LIB_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME}
      PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
      PRIVATE_HEADER DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_INCLUDE_DIR_NAME}
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME}
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_DIR_NAME})
endfunction()

function(ANTHEM_TEST_INSTALLATION)
  install(TARGETS ${ANTHEM_TEST_NAME}
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_BIN_DIR_NAME})
endfunction()

function(ODE_SCRIPT_INSTALLATION)
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/ode
      DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_SCRIPT_DIR_NAME}
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ODE_TEST_SCRIPT_INSTALLATION)
  ode_script_installation()
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/ode
      DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_TEST_SCRIPT_DIR_NAME}
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ANTHEM_SCRIPT_INSTALLATION)
  ode_script_installation()
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/anthem
      DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_SCRIPT_DIR_NAME}
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ANTHEM_LIB_SCRIPT_INSTALLATION)
  ode_script_installation()
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/lib/anthem
  #     DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_SCRIPT_DIR_NAME}
  #     FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ANTHEM_TEST_SCRIPT_INSTALLATION)
  ode_test_script_installation()
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/anthem
      DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_TEST_SCRIPT_DIR_NAME}
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(ADD_ODE_INSTALLATION_TARGET TYPE)
  if(${TYPE} STREQUAL lib)
    if(NOT ODE_INSTALL_ONLY_SCRIPTS)
      ode_installation()
    endif()
    ode_script_installation()
  elseif(${TYPE} STREQUAL test)
    if(NOT ODE_INSTALL_ONLY_SCRIPTS)
      ode_test_installation()
    endif()
    ode_test_script_installation()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ODE_TYPE) is ${ODE_TYPE} and thus \
invalid – please set it to either 'lib' or 'test'")
  endif()
endfunction()

function(ADD_ANTHEM_INSTALLATION_TARGET TYPE)
  if(${TYPE} STREQUAL exe)
    if(NOT ODE_INSTALL_ONLY_SCRIPTS)
      anthem_installation()
    endif()
    anthem_script_installation()
  elseif(${TYPE} STREQUAL lib)
    if(NOT ODE_INSTALL_ONLY_SCRIPTS)
      anthem_lib_installation()
    endif()
    anthem_lib_script_installation()
  elseif(${TYPE} STREQUAL test)
    if(NOT ODE_INSTALL_ONLY_SCRIPTS)
      anthem_test_installation()
    endif()
    anthem_test_script_installation()
  else()
    message(FATAL_ERROR
        "The value of the executable type (ANTHEM_TYPE) is ${ANTHEM_TYPE} and \
thus invalid – please set it to either 'exe', 'lib', or 'test'")
  endif()
endfunction()
