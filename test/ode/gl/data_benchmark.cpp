/// The benchmarks of the utility functions which allow to get data from the
/// OpenGL API.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/gl/data.h"

#include <benchmark/benchmark.h>

static void ode_gl_data_vendor(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::get_vendor();
  }
}

BENCHMARK(ode_gl_data_vendor);

static void ode_gl_data_renderer(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::get_renderer();
  }
}

BENCHMARK(ode_gl_data_renderer);

static void ode_gl_data_version(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::get_version();
  }
}

BENCHMARK(ode_gl_data_version);

static void ode_gl_data_shading_language_version(benchmark::State& state)
{
  for (auto _ : state)
  {
    auto r = ode::gl::get_shading_language_version();
  }
}

BENCHMARK(ode_gl_data_shading_language_version);
