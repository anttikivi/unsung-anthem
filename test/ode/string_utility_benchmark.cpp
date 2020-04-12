/// The benchmarks of the general string-related utilities.
/// \file
/// \author Antti Kivi
/// \date 12 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/string_utility.h"

#include <benchmark/benchmark.h>

static void ode_string_utility_trim(benchmark::State& state)
{
  const std::string str{"   this is a string        "};

  for (auto _ : state)
  {
    ode::trim(str);
  }
}

BENCHMARK(ode_string_utility_trim);

static void ode_string_utility_stob_false(benchmark::State& state)
{
  const std::string str{"False"};

  for (auto _ : state)
  {
    ode::stob(str);
  }
}

BENCHMARK(ode_string_utility_stob_false);

static void ode_string_utility_stob_true(benchmark::State& state)
{
  const std::string str{"True"};

  for (auto _ : state)
  {
    ode::stob(str);
  }
}

BENCHMARK(ode_string_utility_stob_true);
