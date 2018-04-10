//===-------------------------- script_test.cpp -----------------*- C++ -*-===//
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
/// \file script_test.cpp
/// \brief Tests of the definitions of the utilities for Lua scripts.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/version.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

#include <SDL2/SDL.h>

TEST(ode_sdl_version, compiled)
{
  auto v = ode::sdl::compiled_version();

  ASSERT_EQ(v.major, 2);
  ASSERT_EQ(v.minor, 0);
  ASSERT_EQ(v.patch, 8);

  SDL_version compiled;
  SDL_VERSION(&compiled);

  ASSERT_EQ(v.major, compiled.major);
  ASSERT_EQ(v.minor, compiled.minor);
  ASSERT_EQ(v.patch, compiled.patch);
}

TEST(ode_sdl_version, linked)
{
  auto v = ode::sdl::linked_version();

  ASSERT_EQ(v.major, 2);
  ASSERT_EQ(v.minor, 0);
  ASSERT_EQ(v.patch, 8);

  SDL_version linked;
  SDL_GetVersion(&linked);

  ASSERT_EQ(v.major, linked.major);
  ASSERT_EQ(v.minor, linked.minor);
  ASSERT_EQ(v.patch, linked.patch);
}

#if ODE_TEST_BENCHMARKING

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

#endif // ODE_TEST_BENCHMARKING
