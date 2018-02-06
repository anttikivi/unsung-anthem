#===------------------------ ExternalSources.cmake -------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (c) 2018 Venturesome Stone
# Licensed under GNU Affero General Public License v3.0

function(SET_GLAD_SOURCES)

  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/glad.c)
  set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)

endfunction()

function(SET_LUA_SOURCES)

  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lauxlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lopcodes.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lopcodes.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lstate.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lobject.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lmathlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/loadlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lvm.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lfunc.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lstrlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lua.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/linit.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lstring.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lundump.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lctype.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/luac.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ltable.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldump.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/loslib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lgc.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lzio.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldblib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lutf8lib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lmem.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lcorolib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lcode.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ltablib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lbitlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lapi.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lbaselib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldebug.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lparser.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/llex.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ltm.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldo.c)

  set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)

endfunction()
