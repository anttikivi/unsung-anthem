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
      ${ODE_NAME}
      ${ODE_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(ODE_INSTALLATION)
  install(TARGETS
      ${ODE_NAME}
      ${ODE_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(LIB_INSTALLATION)
  install(TARGETS
      ${ANTHEM_LIB_NAME}
      ${ANTHEM_LIB_NAME}_shared
      ${ODE_NAME}
      ${ODE_NAME}_shared
      RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
      LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
      ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
endfunction()

function(TEST_INSTALLATION)
  if(${ODE_ONLY})
    install(
        TARGETS ${ODE_TEST_EXECUTABLE_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  else()
    install(
        TARGETS ${ANTHEM_TEST_EXECUTABLE_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
  endif()
endfunction()

function(ADD_INSTALLATION_TARGET TYPE)
  if(${TYPE} STREQUAL exe)
    main_installation()
  elseif(${TYPE} STREQUAL lib)
    if(${ODE_ONLY})
      ode_installation()
    else()
      lib_installation()
    endif()
  elseif(${TYPE} STREQUAL test)
    test_installation()
  else()
    if(${ODE_ONLY})
      message(FATAL_ERROR
          "The value of the executable type (ODE_EXECUTABLE_TYPE) is \
${ODE_EXECUTABLE_TYPE} and thus invalid – please set it to either \
'lib' or 'test'")
    else()
      message(FATAL_ERROR
          "The value of the executable type (ANTHEM_EXECUTABLE_TYPE) is \
${ANTHEM_EXECUTABLE_TYPE} and thus invalid – please set it to either \
'exe', 'lib', or 'test'")
    endif()
  endif()
endfunction()
