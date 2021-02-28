# Copyright (c) 2018–2020 Antti Kivi
# Licensed under the Effective Elegy Licence

function(SET_GLAD_SOURCES)

  list(APPEND ODE_SOURCES ${COMPOSER_LOCAL_PREFIX}/src/glad.c)
  set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)

endfunction()
