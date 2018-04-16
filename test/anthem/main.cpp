//===------------------------------ main.cpp --------------------*- C++ -*-===//
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
/// \file main.cpp
/// \brief The main function of the Unsung Anthem tests.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/clean_up.h"
#include "ode/common/run_test.h"
#include "ode/common/set_up.h"

#include "ode/config.h"

#include "anthem/logger.h"

#include "anthem/logging_config.h"

#include <SDL2/SDL.h>

#if ODE_TEST_USE_NULL_SINK
# include <spdlog/sinks/null_sink.h>
#endif // ODE_TEST_USE_NULL_SINK

int main(int argc, char* argv[])
{
  if constexpr (ode::test_use_null_sink)
  {
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();

    anthem::logger = ode::create_logger(
        "anthem_test_logger",
        anthem::logger_pattern,
        anthem::logger_level,
        null_sink);
  }
  else
  {
    anthem::logger = ode::create_logger(
        "anthem_test_logger",
        anthem::logger_pattern,
        anthem::logger_level);
  }

  ode::test::set_up(argc, argv);
  const int result = ode::test::run(argc, argv);
  ode::test::clean_up();
  return result;
}
