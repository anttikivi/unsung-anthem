/// The benchmarks of the utilities for Lua scripts.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/script.h"

#include <benchmark/benchmark.h>

#include "ode/config.h"
#include "ode/filesystem/path.h"

static void ode_load_script_file(benchmark::State& state)
{
  const std::string filename = std::string{ode::test_script_root} +
      ode::filesystem::path::preferred_separator + "script.lua";

  lua_State* l = luaL_newstate();

  for (auto _ : state)
  {
    ode::lua::load_script_file(l, filename.c_str());
  }

  lua_close(l);
}

BENCHMARK(ode_load_script_file);
