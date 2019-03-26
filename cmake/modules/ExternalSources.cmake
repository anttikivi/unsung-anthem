#===------------------------ ExternalSources.cmake -------------------------===#
#
#                         Obliging Ode & Unsung Anthem
#
# This source file is part of the Obliging Ode and Unsung Anthem open source
# projects.
#
# Copyright (C) 2019 Antti Kivi
# All rights reserved

function(SET_GLAD_SOURCES)

  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/glad.c)
  set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)

endfunction()

function(SET_LUA_SOURCES)

  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lapi.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lcode.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lctype.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldebug.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldo.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldump.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lfunc.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lgc.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/llex.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lmem.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lobject.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lopcodes.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lparser.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lstate.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lstring.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ltable.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ltm.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lundump.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lvm.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lzio.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lauxlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lbaselib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lbitlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lcorolib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ldblib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/liolib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lmathlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/loslib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lstrlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/ltablib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lutf8lib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/loadlib.c)
  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/linit.c)

  list(APPEND ODE_SOURCES ${ODE_INSTALL_PREFIX}/src/lua.c)

  set(ODE_SOURCES ${ODE_SOURCES} PARENT_SCOPE)

endfunction()

function(SET_GTEST_SOURCES)

  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/gtest/src/gtest-all.cc)

  set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)

endfunction()

function(SET_BENCHMARK_SOURCES)

  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/benchmark_register.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/benchmark.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/colorprint.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/commandlineflags.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/complexity.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/console_reporter.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/counter.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/csv_reporter.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/json_reporter.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/reporter.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/sleep.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/statistics.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/string_util.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/sysinfo.cc)
  list(APPEND ODE_TEST_SOURCES ${ODE_INSTALL_PREFIX}/src/benchmark/timers.cc)

  add_definitions(-DHAVE_STD_REGEX=1)

  set(ODE_TEST_SOURCES ${ODE_TEST_SOURCES} PARENT_SCOPE)

endfunction()
