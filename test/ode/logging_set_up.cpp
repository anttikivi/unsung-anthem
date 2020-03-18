//===------------------------- logging_set_up.cpp ---------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file logging_set_up.cpp
/// \brief The definitions of the set up functions for the tests and benchmarks
/// of the logging functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging_set_up.h"

#include "ode/config.h"

#include "ode/logging_config.h"

#include <spdlog/sinks/null_sink.h>

ode::logger_t create_logging_test_logger()
{
  if constexpr (ode::test_use_null_sink)
  {
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();

    return ode::create_logger(
        "test_logger_ode",
        ode::logger_pattern,
        ode::logger_level,
        null_sink);
  }
  else
  {
    return ode::create_logger(
        "test_logger_ode",
        ode::logger_pattern,
        ode::logger_level);
  }
}

ode::logger_t create_logging_benchmark_logger()
{
  auto benchmark_sink = std::make_shared<spdlog::sinks::null_sink_st>();

  return ode::create_logger(
      "benchmark_logger_ode",
      ode::logger_pattern,
      ode::logger_level,
      benchmark_sink);
}
