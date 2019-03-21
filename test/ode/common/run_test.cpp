//===---------------------------- run_test.cpp ------------------*- C++ -*-===//
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
/// \file run_test.cpp
/// \brief The definitions of the common running functions of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2019 Antti Kivi
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
    const int result = RUN_ALL_TESTS();

#if ODE_TEST_BENCHMARKING

    ::benchmark::RunSpecifiedBenchmarks();

#endif // ODE_TEST_BENCHMARKING

    return result;
  }
} // namespace ode::test
