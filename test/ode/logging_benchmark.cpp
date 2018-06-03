//===----------------------- logging_benchmark.cpp --------------*- C++ -*-===//
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
/// \file logging_benchmark.cpp
/// \brief The benchmarks of the logging-related utility functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging.h"

#include "ode/logging_set_up.h"

#include <benchmark/benchmark.h>

static void ode_logging_trace(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::trace(
        test_log,
        "This is a benchmarking {}-level message",
        "trace");
  }
}

BENCHMARK(ode_logging_trace);

static void ode_logging_debug(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::debug(
        test_log,
        "This is a benchmarking {}-level message",
        "debug");
  }
}

BENCHMARK(ode_logging_debug);

static void ode_logging_info(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::info(
        test_log,
        "This is a benchmarking {}-level message",
        "info");
  }
}

BENCHMARK(ode_logging_info);

static void ode_logging_warn(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::warn(
        test_log,
        "This is a benchmarking {}-level message",
        "warn");
  }
}

BENCHMARK(ode_logging_warn);

static void ode_logging_error(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::error(
        test_log,
        "This is a benchmarking {}-level message",
        "error");
  }
}

BENCHMARK(ode_logging_error);

static void ode_logging_critical(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::critical(
        test_log,
        "This is a benchmarking {}-level message",
        "critical");
  }
}

BENCHMARK(ode_logging_critical);

static void ode_logging_trace_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::trace(test_log, 5534.3334568854928853923);
  }
}

BENCHMARK(ode_logging_trace_number);

static void ode_logging_debug_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::debug(test_log, 5534.3334568854928853923);
  }
}

BENCHMARK(ode_logging_debug_number);

static void ode_logging_info_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::info(test_log, 5534.3334568854928853923);
  }
}

BENCHMARK(ode_logging_info_number);

static void ode_logging_warn_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::warn(test_log, 5534.3334568854928853923);
  }
}

BENCHMARK(ode_logging_warn_number);

static void ode_logging_error_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::error(test_log, 5534.3334568854928853923);
  }
}

BENCHMARK(ode_logging_error_number);

static void ode_logging_critical_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ode::logging::critical(test_log, 5534.3334568854928853923);
  }
}

BENCHMARK(ode_logging_critical_number);
