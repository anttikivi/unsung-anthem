//===------------------------ state_benchmark.cpp ---------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file state_benchmark.cpp
/// \brief The benchmarks of the Lua state.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

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
