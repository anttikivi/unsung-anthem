//===------------------------ script_benchmark.cpp --------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file script_benchmark.cpp
/// \brief Benchmarks of the definitions of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/lua/script.h"

#include "ode/filesystem/path.h"

#include "ode/config.h"

#include <benchmark/benchmark.h>

static void ode_load_script_file(benchmark::State& state)
{
  const std::string filename = 
      std::string{ode::test_script_root}
      + ode::filesystem::path::preferred_separator
      + "script.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::load_script_file(l, filename.c_str());
  }

  lua_close(l);
}

BENCHMARK(ode_load_script_file);