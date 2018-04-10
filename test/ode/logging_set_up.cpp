//===------------------------- logging_set_up.cpp ---------------*- C++ -*-===//
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
/// \file logging_set_up.cpp
/// \brief Definitions of set up functions for tests and benchmarks of logging
/// functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging_set_up.h"

#include "ode/logging_config.h"

#include <spdlog/sinks/null_sink.h>

ode::logger_t create_logging_test_logger()
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
