# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(CREATE_ANTHEM_EXECUTABLE_INSTALL_TARGET)
  install(TARGETS ${COMPOSER_ANTHEM_TARGET} RUNTIME DESTINATION bin)
endfunction()

function(CREATE_ANTHEM_TEST_EXECUTABLE_INSTALL_TARGET)
  install(TARGETS ${COMPOSER_ANTHEM_TEST_TARGET} RUNTIME DESTINATION bin)
endfunction()

function(CREATE_ODE_SCRIPTS_INSTALL_TARGET)
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/ode
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/ode
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(CREATE_ODE_TEST_SCRIPTS_INSTALL_TARGET)
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/ode
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/ode
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(CREATE_ANTHEM_SCRIPTS_INSTALL_TARGET)
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/anthem
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/anthem
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(CREATE_ANTHEM_LIB_SCRIPTS_INSTALL_TARGET)
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/lib/anthem
  #     DESTINATION ${CMAKE_INSTALL_PREFIX}/${ODE_LIB_SCRIPT_DIR_NAME}
  #     FILES_MATCHING PATTERN "*.lua")
endfunction()

function(CREATE_ANTHEM_TEST_SCRIPTS_INSTALL_TARGET)
  # TODO Reserved for a world with newer CMake versions
  # install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/anthem
  #     TYPE LIB
  #     FILES_MATCHING PATTERN "*.lua")
  install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/script/test/anthem
      DESTINATION lib
      FILES_MATCHING PATTERN "*.lua")
endfunction()

function(CREATE_INSTALL_TARGETS)
  # if(ODE_BUILD_STATIC)
  #   create_ode_static_install_target()
  # endif()
  # if(ODE_BUILD_SHARED)
  #   create_ode_shared_install_target()
  # endif()
  create_anthem_executable_install_target()
  # if(ANTHEM_BUILD_STATIC)
  #   create_anthem_static_install_target()
  # endif()
  # if(ANTHEM_BUILD_SHARED)
  #   create_anthem_shared_install_target()
  # endif()
  create_ode_scripts_install_target()
  create_anthem_scripts_install_target()
  create_anthem_lib_scripts_install_target()
  if(COMPOSER_BUILD_TEST)
    create_anthem_test_executable_install_target()
    create_ode_test_scripts_install_target()
    create_anthem_test_scripts_install_target()
  endif()
endfunction()
