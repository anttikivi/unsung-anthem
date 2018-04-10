//===--------------------------- data_test.cpp ------------------*- C++ -*-===//
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
/// \file data_test.cpp
/// \brief Tests of definitions of utility functions which allow to get data
/// from the OpenGL API.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/gl/data.h"

#include <cstring>

#include "ode/argv_t.h"
#include "ode/execution_info.h"
#include "ode/initialize.h"
#include "ode/pixel_count.h"
#include "ode/quit.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

TEST(ode_gl_data, vendor)
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

  auto original = glGetString(GL_VENDOR);
  std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
  auto s = std::string{reinterpret_cast<const char*>(original), len};

  auto r = ode::gl::vendor();

  ASSERT_EQ(r, s);

  ode::quit_graphics(graphics_context);
}

TEST(ode_gl_data, renderer)
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

  auto original = glGetString(GL_RENDERER);
  std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
  auto s = std::string{reinterpret_cast<const char*>(original), len};

  auto r = ode::gl::renderer();

  ASSERT_EQ(r, s);

  ode::quit_graphics(graphics_context);
}

TEST(ode_gl_data, version)
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

  auto original = glGetString(GL_VERSION);
  std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
  auto s = std::string{reinterpret_cast<const char*>(original), len};

  auto r = ode::gl::version();

  ASSERT_EQ(r, s);

  ode::quit_graphics(graphics_context);
}

TEST(ode_gl_data, shading_language_version)
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

  auto original = glGetString(GL_SHADING_LANGUAGE_VERSION);
  std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
  auto s = std::string{reinterpret_cast<const char*>(original), len};

  auto r = ode::gl::shading_language_version();

  ASSERT_EQ(r, s);

  ode::quit_graphics(graphics_context);
}

#if ODE_TEST_BENCHMARKING

static void ode_gl_data_vendor(benchmark::State& state)
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

BENCHMARK(ode_gl_data_vendor);

static void ode_gl_data_renderer(benchmark::State& state)
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

BENCHMARK(ode_gl_data_renderer);

static void ode_gl_data_version(benchmark::State& state)
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

BENCHMARK(ode_gl_data_version);

static void ode_gl_data_shading_language_version(benchmark::State& state)
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

BENCHMARK(ode_gl_data_shading_language_version);

#endif // ODE_TEST_BENCHMARKING
