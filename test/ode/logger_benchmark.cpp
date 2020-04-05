/// The benchmarks of the main logging functions.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/logger.h"

#include <benchmark/benchmark.h>

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

static void ode_logger_trace_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_TRACE(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_trace_macro_number);

static void ode_logger_debug_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_DEBUG(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_debug_macro_number);

static void ode_logger_info_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_INFO(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_info_macro_number);

static void ode_logger_warn_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_WARN(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_warn_macro_number);

static void ode_logger_error_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_ERROR(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_error_macro_number);

static void ode_logger_critical_macro_number(benchmark::State& state)
{
  for (auto _ : state)
  {
    ODE_CRITICAL(5534.3334568854928853923);
  }
}

BENCHMARK(ode_logger_critical_macro_number);

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
