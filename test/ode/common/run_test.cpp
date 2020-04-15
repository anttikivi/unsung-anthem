/// The definitions of the common running functions of the tests.
/// \file
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/common/run_test.h"

#if ODE_TEST_BENCHMARKING
#  include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

namespace ode::test
{
  int run_tests(int argc, char* argv[])
  {
    const int result = RUN_ALL_TESTS();

    return result;
  }

#if ODE_TEST_BENCHMARKING

  int run_benchmarks(int argc, char* argv[])
  {
    ::benchmark::RunSpecifiedBenchmarks();

    return 0;
  }

#endif // ODE_TEST_BENCHMARKING

} // namespace ode::test
