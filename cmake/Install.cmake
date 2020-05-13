# Copyright (c) 2019–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(CREATE_ODE_STATIC_INSTALL_TARGET)
  install(TARGETS ${ODE_STATIC_NAME}
      RUNTIME DESTINATION bin
      PUBLIC_HEADER DESTINATION include
      PRIVATE_HEADER DESTINATION include
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib)
endfunction()

function(CREATE_ODE_SHARED_INSTALL_TARGET)
  install(TARGETS ${ODE_SHARED_NAME}
      RUNTIME DESTINATION bin
      PUBLIC_HEADER DESTINATION include
      PRIVATE_HEADER DESTINATION include
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib)
endfunction()

function(CREATE_ANTHEM_EXECUTABLE_INSTALL_TARGET)
  install(TARGETS ${ANTHEM_NAME} RUNTIME DESTINATION bin)
endfunction()

function(CREATE_ANTHEM_STATIC_INSTALL_TARGET)
  install(TARGETS ${ANTHEM_STATIC_NAME}
      RUNTIME DESTINATION bin
      PUBLIC_HEADER DESTINATION include
      PRIVATE_HEADER DESTINATION include
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib)
endfunction()

function(CREATE_ANTHEM_SHARED_INSTALL_TARGET)
  install(TARGETS ${ANTHEM_SHARED_NAME}
      RUNTIME DESTINATION bin
      PUBLIC_HEADER DESTINATION include
      PRIVATE_HEADER DESTINATION include
      LIBRARY DESTINATION lib
      ARCHIVE DESTINATION lib)
endfunction()

function(CREATE_ANTHEM_TEST_EXECUTABLE_INSTALL_TARGET)
  install(TARGETS ${ANTHEM_TEST_NAME} RUNTIME DESTINATION bin)
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
  if(ODE_BUILD_STATIC)
    create_ode_static_install_target()
  endif()
  if(ODE_BUILD_SHARED)
    create_ode_shared_install_target()
  endif()
  create_anthem_executable_install_target()
  if(ANTHEM_BUILD_STATIC)
    create_anthem_static_install_target()
  endif()
  if(ANTHEM_BUILD_SHARED)
    create_anthem_shared_install_target()
  endif()
  create_ode_scripts_install_target()
  create_anthem_scripts_install_target()
  create_anthem_lib_scripts_install_target()
  if(ODE_BUILD_TEST)
    create_anthem_test_executable_install_target()
    create_ode_test_scripts_install_target()
    create_anthem_test_scripts_install_target()
  endif()
endfunction()
