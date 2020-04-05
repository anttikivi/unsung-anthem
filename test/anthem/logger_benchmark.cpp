/// The benchmarks of the main logging functions.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/logger.h"

#include <benchmark/benchmark.h>

static void anthem_logger_trace_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_TRACE(
        "This is a benchmarking {}-level message in a macro",
        "trace");
  }
}

BENCHMARK(anthem_logger_trace_macro);

static void anthem_logger_debug_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_DEBUG(
        "This is a benchmarking {}-level message in a macro",
        "debug");
  }
}

BENCHMARK(anthem_logger_debug_macro);

static void anthem_logger_info_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_INFO("This is a benchmarking {}-level message in a macro", "info");
  }
}

BENCHMARK(anthem_logger_info_macro);

static void anthem_logger_warn_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_WARN("This is a benchmarking {}-level message in a macro", "warn");
  }
}

BENCHMARK(anthem_logger_warn_macro);

static void anthem_logger_error_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_ERROR(
        "This is a benchmarking {}-level message in a macro",
        "error");
  }
}

BENCHMARK(anthem_logger_error_macro);

static void anthem_logger_critical_macro(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_CRITICAL(
        "This is a benchmarking {}-level message in a macro",
        "critical");
  }
}

BENCHMARK(anthem_logger_critical_macro);

static void anthem_logger_trace_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_TRACE(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_trace_macro_number);

static void anthem_logger_debug_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_DEBUG(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_debug_macro_number);

static void anthem_logger_info_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_INFO(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_info_macro_number);

static void anthem_logger_warn_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_WARN(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_warn_macro_number);

static void anthem_logger_error_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_ERROR(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_error_macro_number);

static void anthem_logger_critical_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ANTHEM_CRITICAL(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_critical_macro_number);

static void anthem_logger_trace(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::trace("This is a benchmarking {}-level message", "trace");
  }
}

BENCHMARK(anthem_logger_trace);

static void anthem_logger_debug(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::debug("This is a benchmarking {}-level message", "debug");
  }
}

BENCHMARK(anthem_logger_debug);

static void anthem_logger_info(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::info("This is a benchmarking {}-level message", "info");
  }
}

BENCHMARK(anthem_logger_info);

static void anthem_logger_warn(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::warn("This is a benchmarking {}-level message", "warn");
  }
}

BENCHMARK(anthem_logger_warn);

static void anthem_logger_error(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::error("This is a benchmarking {}-level message", "error");
  }
}

BENCHMARK(anthem_logger_error);

static void anthem_logger_critical(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::critical(
        "This is a benchmarking {}-level message",
        "critical");
  }
}

BENCHMARK(anthem_logger_critical);

static void anthem_logger_trace_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::trace(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_trace_number);

static void anthem_logger_debug_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::debug(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_debug_number);

static void anthem_logger_info_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::info(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_info_number);

static void anthem_logger_warn_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::warn(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_warn_number);

static void anthem_logger_error_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::error(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_error_number);

static void anthem_logger_critical_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    anthem::logging::critical(5534.3334568854928853923);
  }
}

BENCHMARK(anthem_logger_critical_number);
