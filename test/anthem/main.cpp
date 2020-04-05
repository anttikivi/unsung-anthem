/// The main function of the tests.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/common/clean_up.h"
#include "ode/common/run_test.h"
#include "ode/common/set_up.h"

#include "ode/config.h"

#include "anthem/logger.h"

#include "anthem/logging_config.h"

#include <SDL2/SDL.h>

#include <spdlog/sinks/null_sink.h>

int main(int argc, char* argv[])
{
  if constexpr (::ode::test_use_null_sink)
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

  ode::test::set_up_tests(argc, argv);

  const int result_tests = ode::test::run_tests(argc, argv);

#if ODE_TEST_BENCHMARKING

  auto benchmark_sink = std::make_shared<spdlog::sinks::null_sink_st>();

  anthem::logger = ode::create_logger(
      "anthem_benchmark_logger",
      anthem::logger_pattern,
      anthem::logger_level,
      benchmark_sink);

  ode::test::set_up_benchmarks(argc, argv);

  const int result_benchmarks = ode::test::run_benchmarks(argc, argv);

#endif // ODE_TEST_BENCHMARKING

  ode::test::clean_up();

  return result_tests;
}
