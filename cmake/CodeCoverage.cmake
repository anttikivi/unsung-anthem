# Copyright (c) 2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(ADD_COVERAGE_TARGET)
  add_library(ode_coverage_config INTERFACE)

  if(ODE_CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(ode_coverage_config INTERFACE -O0 -g --coverage)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
      target_link_options(ode_coverage_config INTERFACE --coverage)
    else()
      target_link_libraries(ode_coverage_config INTERFACE --coverage)
    endif()
  endif()
endfunction()
