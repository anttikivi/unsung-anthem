//===----------------------------- set_up.cpp -------------------*- C++ -*-===//
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
/// \file set_up.cpp
/// \brief Definition of the common set up function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/set_up.h"

#include "ode/logger.h"
#include "ode/filesystem/path.h"

#include "ode/config.h"
#include "ode/logging_config.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

#include <spdlog/sinks/null_sink.h>

namespace ode::test
{
  int set_up(int argc, char* argv[])
  {
    auto null_sink = std::make_shared<spdlog::sinks::null_sink_st>();

    ode::logger = ode::create_logger(
        "ode_test_logger",
        ode::logger_pattern,
        ode::logger_level,
        null_sink);

    ::testing::InitGoogleTest(&argc, argv);

#if ODE_TEST_BENCHMARKING

    ::benchmark::Initialize(&argc, argv);

    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
    {
      return 5;
    }

#endif // ODE_TEST_BENCHMARKING

    return 0;
  }
} // namespace ode::test
