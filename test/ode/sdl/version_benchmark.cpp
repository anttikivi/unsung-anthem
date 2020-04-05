/// The benchmarks of the Simple DirectMedia Layer version utility functions.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/sdl/sdl_version.h"

#include <benchmark/benchmark.h>

static void ode_sdl_compiled_version(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto v = ode::sdl::compiled_version();
  }
}

BENCHMARK(ode_sdl_compiled_version);

static void ode_sdl_linked_version(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto v = ode::sdl::linked_version();
  }
}

BENCHMARK(ode_sdl_linked_version);
