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
/// \brief Tests of declarations of main logging functions of Unsung Anthem.
/// \author Antti Kivi
/// \date 8 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/logger.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

TEST(anthem_logger_macro, trace)
{
  ASSERT_NO_THROW(
      ANTHEM_TRACE("This is a test {}-level message in a macro", "trace"));
  ASSERT_NO_THROW(ANTHEM_TRACE(1));
}

TEST(anthem_logger_macro, debug)
{
  ASSERT_NO_THROW(
      ANTHEM_DEBUG("This is a test {}-level message in a macro", "debug"));
  ASSERT_NO_THROW(ANTHEM_DEBUG(2));
}

TEST(anthem_logger_macro, info)
{
  ASSERT_NO_THROW(
      ANTHEM_INFO("This is a test {}-level message in a macro", "info"));
  ASSERT_NO_THROW(ANTHEM_INFO(3));
}

TEST(anthem_logger_macro, warn)
{
  ASSERT_NO_THROW(
      ANTHEM_WARN("This is a test {}-level message in a macro", "warning"));
  ASSERT_NO_THROW(ANTHEM_WARN(4));
}

TEST(anthem_logger_macro, error)
{
  ASSERT_NO_THROW(
      ANTHEM_ERROR("This is a test {}-level message in a macro", "warning"));
  ASSERT_NO_THROW(ANTHEM_ERROR(5));
}

TEST(anthem_logger_macro, critical)
{
  ASSERT_NO_THROW(ANTHEM_CRITICAL(
      "This is a test {}-level message in a macro",
      "critical"));
  ASSERT_NO_THROW(ANTHEM_CRITICAL(6));
}

TEST(anthem_logger, trace)
{
  ASSERT_NO_THROW(
      anthem::logging::trace("This is a test {}-level message", "trace"));
  ASSERT_NO_THROW(anthem::logging::trace(1));
}

TEST(anthem_logger, debug)
{
  ASSERT_NO_THROW(
      anthem::logging::debug("This is a test {}-level message", "debug"));
  ASSERT_NO_THROW(anthem::logging::debug(2));
}

TEST(anthem_logger, info)
{
  ASSERT_NO_THROW(
      anthem::logging::info("This is a test {}-level message", "info"));
  ASSERT_NO_THROW(anthem::logging::info(3));
}

TEST(anthem_logger, warn)
{
  ASSERT_NO_THROW(
      anthem::logging::warn("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(anthem::logging::warn(4));
}

TEST(anthem_logger, error)
{
  ASSERT_NO_THROW(
      anthem::logging::error("This is a test {}-level message", "warning"));
  ASSERT_NO_THROW(anthem::logging::error(5));
}

TEST(anthem_logger, critical)
{
  ASSERT_NO_THROW(anthem::logging::critical(
      "This is a test {}-level message",
      "critical"));
  ASSERT_NO_THROW(anthem::logging::critical(6));
}

#if ODE_TEST_BENCHMARKING

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

#endif // ODE_TEST_BENCHMARKING
