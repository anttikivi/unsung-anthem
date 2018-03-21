//===---------------------------- run_test.cpp ------------------*- C++ -*-===//
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
/// \file run_test.cpp
/// \brief Definition of the common running function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/run_test.h"

#if ODE_TEST_BENCHMARKING
# include <benchmark/benchmark.h>
#endif // ODE_TEST_BENCHMARKING

#include <gtest/gtest.h>

namespace ode::test
{
  int run(int argc, char* argv[])
  {
    ::testing::InitGoogleTest(&argc, argv);

    const int result = RUN_ALL_TESTS();

#if ODE_TEST_BENCHMARKING

    if (::benchmark::ReportUnrecognizedArguments(argc, argv))
    {
      return 5;
    }

    ::benchmark::RunSpecifiedBenchmarks();

#endif // ODE_TEST_BENCHMARKING

    return result;
  }
} // namespace ode::test
