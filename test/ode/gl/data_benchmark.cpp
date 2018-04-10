//===------------------------- data_benchmark.cpp ---------------*- C++ -*-===//
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
/// \file data_benchmark.cpp
/// \brief Benchmarks of definitions of utility functions which allow to get
/// data from the OpenGL API.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/gl/data.h"

#include <benchmark/benchmark.h>

static void ode_gl_data_vendor(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::vendor();
  }
}

BENCHMARK(ode_gl_data_vendor);

static void ode_gl_data_renderer(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::renderer();
  }
}

BENCHMARK(ode_gl_data_renderer);

static void ode_gl_data_version(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::version();
  }
}

BENCHMARK(ode_gl_data_version);

static void ode_gl_data_shading_language_version(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::shading_language_version();
  }
}

BENCHMARK(ode_gl_data_shading_language_version);
