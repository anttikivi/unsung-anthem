/// The benchmarks of the Lua state.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/lua/state.h"

#include <benchmark/benchmark.h>

static void ode_lua_make_state(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto state = ode::lua::make_state();
  }
}

BENCHMARK(ode_lua_make_state);
