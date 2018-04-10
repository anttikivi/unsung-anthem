//===----------------------- version_benchmark.cpp --------------*- C++ -*-===//
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
/// \file version_benchmark.cpp
/// \brief Benchmarks of definitions of Simple DirectMedia Layer version
/// utility functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/version.h"

#include <benchmark/benchmark.h>

#include <SDL2/SDL.h>

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
