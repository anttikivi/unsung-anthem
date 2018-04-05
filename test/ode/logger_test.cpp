//===-------------------------- logger_test.cpp -----------------*- C++ -*-===//
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
/// \file logger_test.cpp
/// \brief Tests of declarations of main logging functions of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logger.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

TEST(ode_logger_macro, trace)
{
  ASSERT_NO_THROW(
      ODE_TRACE("This is a test {}-level message in a macro", "trace"));
}

TEST(ode_logger_macro, debug)
{
  ASSERT_NO_THROW(
      ODE_DEBUG("This is a test {}-level message in a macro", "debug"));
}

TEST(ode_logger_macro, info)
{
  ASSERT_NO_THROW(
      ODE_INFO("This is a test {}-level message in a macro", "info"));
}

TEST(ode_logger_macro, warn)
{
  ASSERT_NO_THROW(
      ODE_WARN("This is a test {}-level message in a macro", "warning"));
}

TEST(ode_logger_macro, error)
{
  ASSERT_NO_THROW(
      ODE_ERROR("This is a test {}-level message in a macro", "warning"));
}

TEST(ode_logger_macro, critical)
{
  ASSERT_NO_THROW(
      ODE_CRITICAL("This is a test {}-level message in a macro", "critical"));
}

TEST(ode_logger, trace)
{
  ASSERT_NO_THROW(
      ode::logging::trace("This is a test {}-level message", "trace"));
  ASSERT_NO_THROW(ode::logging::trace(1));
}

TEST(ode_logger, debug)
{
  ASSERT_NO_THROW(
      ode::logging::debug("This is a test {}-level message", "debug"));
  ASSERT_NO_THROW(ode::logging::debug(2));
}

TEST(ode_logger, info)
{
  ASSERT_NO_THROW(
      ode::logging::info("This is a test {}-level message", "info"));
  ASSERT_NO_THROW(ode::logging::info(3));
}

TEST(ode_logger, warn)
{
  ASSERT_NO_THROW(
      ode::logging::warn("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(ode::logging::warn(4));
}

TEST(ode_logger, error)
{
  ASSERT_NO_THROW(
      ode::logging::error("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(ode::logging::error(5));
}

TEST(ode_logger, critical)
{
  ASSERT_NO_THROW(
      ode::logging::critical("This is a test {}-level message", "critical"));
  ASSERT_NO_THROW(ode::logging::critical(6));
}

#if ODE_TEST_BENCHMARKING

static void ode_logger_trace_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_TRACE("This is a benchmarking {}-level message in a macro", "trace");
  }
}

BENCHMARK(ode_logger_trace_macro);

static void ode_logger_debug_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_DEBUG("This is a benchmarking {}-level message in a macro", "debug");
  }
}

BENCHMARK(ode_logger_debug_macro);

static void ode_logger_info_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_INFO("This is a benchmarking {}-level message in a macro", "info");
  }
}

BENCHMARK(ode_logger_info_macro);

static void ode_logger_warn_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_WARN("This is a benchmarking {}-level message in a macro", "warn");
  }
}

BENCHMARK(ode_logger_warn_macro);

static void ode_logger_error_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_ERROR("This is a benchmarking {}-level message in a macro", "error");
  }
}

BENCHMARK(ode_logger_error_macro);

static void ode_logger_critical_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_CRITICAL(
        "This is a benchmarking {}-level message in a macro",
        "critical");
  }
}

BENCHMARK(ode_logger_critical_macro);

static void ode_logger_trace(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::trace("This is a benchmarking {}-level message", "trace");
  }
}

BENCHMARK(ode_logger_trace);

static void ode_logger_debug(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::debug("This is a benchmarking {}-level message", "debug");
  }
}

BENCHMARK(ode_logger_debug);

static void ode_logger_info(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::info("This is a benchmarking {}-level message", "info");
  }
}

BENCHMARK(ode_logger_info);

static void ode_logger_warn(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::warn("This is a benchmarking {}-level message", "warn");
  }
}

BENCHMARK(ode_logger_warn);

static void ode_logger_error(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::error("This is a benchmarking {}-level message", "error");
  }
}

BENCHMARK(ode_logger_error);

static void ode_logger_critical(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::critical(
        "This is a benchmarking {}-level message",
        "critical");
  }
}

BENCHMARK(ode_logger_critical);

static void ode_logger_trace_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::trace(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_trace_number);

static void ode_logger_debug_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::debug(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_debug_number);

static void ode_logger_info_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::info(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_info_number);

static void ode_logger_warn_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::warn(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_warn_number);

static void ode_logger_error_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::error(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_error_number);

static void ode_logger_critical_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::critical(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_critical_number);

#endif // ODE_TEST_BENCHMARKING
