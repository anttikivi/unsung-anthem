# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

if(COMPOSER_BUILD_DOCS AND DOXYGEN_FOUND)
  set(docs_srcdir ${CMAKE_CURRENT_SOURCE_DIR})
  set(docs_builddir ${CMAKE_CURRENT_BINARY_DIR})

  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doxygen.cfg.in
      ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg @ONLY)

  add_custom_target(doxygen-anthem
      ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxygen.cfg
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating Obliging Ode and Unsung Anthem Doxygen documentation."
      VERBATIM)

      add_dependencies(${COMPOSER_ANTHEM_TARGET} doxygen-anthem)
endif()
