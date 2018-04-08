//===-------------------------- logging_test.cpp ----------------*- C++ -*-===//
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
/// \file logging_test.cpp
/// \brief Tests of declarations of logging-related utility functions.
/// \author Antti Kivi
/// \date 8 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging.h"

#include "ode/logging_config.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

#include <spdlog/sinks/null_sink.h>

TEST(ode_logging, create_logger)
{
  auto logger_1 = ode::create_logger(
      "test_case_logger_ode_1",
      "[%H.%M:%S] %v",
      spdlog::level::info);

  ASSERT_EQ("test_case_logger_ode_1", logger_1->name());
  ASSERT_EQ(spdlog::level::info, logger_1->level());

  auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();
  auto logger_2 = ode::create_logger(
      "test_case_logger_ode_2",
      "[%H.%M:%S] %v",
      spdlog::level::info,
      null_sink);

  ASSERT_EQ("test_case_logger_ode_2", logger_2->name());
  ASSERT_EQ(spdlog::level::info, logger_2->level());
  ASSERT_EQ(null_sink, logger_2->sinks()[0]);
}

auto create_logging_test_logger()
{
#if ODE_TEST_USE_NULL_SINK

  auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();

  return ode::create_logger(
      "test_logger_ode",
      ode::logger_pattern,
      ode::logger_level,
      null_sink);

#else

  return ode::create_logger(
      "test_logger_ode",
      ode::logger_pattern,
      ode::logger_level);

#endif // !ODE_TEST_USE_NULL_SINK
}

auto test_log = create_logging_test_logger();

TEST(ode_logging, trace)
{
  ASSERT_NO_THROW(ode::logging::trace(
      test_log,
      "This is a test {}-level message",
      "trace"));
  ASSERT_NO_THROW(ode::logging::trace(test_log, 1));
}

TEST(ode_logging, debug)
{
  ASSERT_NO_THROW(ode::logging::debug(
      test_log,
      "This is a test {}-level message",
      "debug"));
  ASSERT_NO_THROW(ode::logging::debug(test_log, 2));
}

TEST(ode_logging, info)
{
  ASSERT_NO_THROW(ode::logging::info(
      test_log,
      "This is a test {}-level message",
      "info"));
  ASSERT_NO_THROW(ode::logging::info(test_log, 3));
}

TEST(ode_logging, warn)
{
  ASSERT_NO_THROW(ode::logging::warn(
      test_log,
      "This is a test {}-level message",
      "warning"));
  ASSERT_NO_THROW(ode::logging::warn(test_log, 4));
}

TEST(ode_logging, error)
{
  ASSERT_NO_THROW(ode::logging::error(
      test_log,
      "This is a test {}-level message",
      "warning"));
  ASSERT_NO_THROW(ode::logging::error(test_log, 5));
}

TEST(ode_logging, critical)
{
  ASSERT_NO_THROW(ode::logging::critical(
      test_log,
      "This is a test {}-level message",
      "critical"));
  ASSERT_NO_THROW(ode::logging::critical(test_log, 6));
}

#if ODE_TEST_BENCHMARKING

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

#endif // ODE_TEST_BENCHMARKING
