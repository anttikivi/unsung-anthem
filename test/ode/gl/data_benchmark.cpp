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

#include "ode/argv_t.h"
#include "ode/execution_info.h"
#include "ode/initialize.h"
#include "ode/pixel_count.h"
#include "ode/quit.h"

#include <benchmark/benchmark.h>

static void ode_gl_data_vendor(benchmark::State& state)
{
  // Use a separate scope to ensure that everything is quit.
  {
    const int argc = 1;
    ode::argv_t argv[] = {"exe"};
    const auto sdl_quit_action = ode::initialize_sdl();
    auto window = ode::initialize_window({
        argc,
        argv,
        0_px,
        0_px,
        "window_name"});
    auto graphics_context = ode::initialize_graphics(window.get());

    for (auto _ : state)
    {
      auto r = ode::gl::vendor();
    }

    ode::quit_graphics(graphics_context);
  }
}

BENCHMARK(ode_gl_data_vendor);

static void ode_gl_data_renderer(benchmark::State& state)
{
  // Use a separate scope to ensure that everything is quit.
  {
    const int argc = 1;
    ode::argv_t argv[] = {"exe"};
    const auto sdl_quit_action = ode::initialize_sdl();
    auto window = ode::initialize_window({
        argc,
        argv,
        0_px,
        0_px,
        "window_name"});
    auto graphics_context = ode::initialize_graphics(window.get());

    for (auto _ : state)
    {
      auto r = ode::gl::renderer();
    }

    ode::quit_graphics(graphics_context);
  }
}

BENCHMARK(ode_gl_data_renderer);

static void ode_gl_data_version(benchmark::State& state)
{
  // Use a separate scope to ensure that everything is quit.
  {
    const int argc = 1;
    ode::argv_t argv[] = {"exe"};
    const auto sdl_quit_action = ode::initialize_sdl();
    auto window = ode::initialize_window({
        argc,
        argv,
        0_px,
        0_px,
        "window_name"});
    auto graphics_context = ode::initialize_graphics(window.get());

    for (auto _ : state)
    {
      auto r = ode::gl::version();
    }

    ode::quit_graphics(graphics_context);
  }
}

BENCHMARK(ode_gl_data_version);

static void ode_gl_data_shading_language_version(benchmark::State& state)
{
  // Use a separate scope to ensure that everything is quit.
  {
    const int argc = 1;
    ode::argv_t argv[] = {"exe"};
    const auto sdl_quit_action = ode::initialize_sdl();
    auto window = ode::initialize_window({
        argc,
        argv,
        0_px,
        0_px,
        "window_name"});
    auto graphics_context = ode::initialize_graphics(window.get());

    for (auto _ : state)
    {
      auto r = ode::gl::shading_language_version();
    }

    ode::quit_graphics(graphics_context);
  }
}

BENCHMARK(ode_gl_data_shading_language_version);
