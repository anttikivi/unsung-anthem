//===-------------------------- logging_test.cpp ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file logging_test.cpp
/// \brief The tests of the logging-related utility functions.
/// \author Antti Kivi
/// \date 8 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging.h"

#include "ode/logging_set_up.h"

#include "ode/logging_config.h"

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
