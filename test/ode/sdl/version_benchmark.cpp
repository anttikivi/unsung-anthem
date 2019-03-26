//===----------------------- version_benchmark.cpp --------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file version_benchmark.cpp
/// \brief The benchmarks of the Simple DirectMedia Layer version utility
/// functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

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
