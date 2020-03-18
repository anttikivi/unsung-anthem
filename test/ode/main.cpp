//===------------------------------ main.cpp --------------------*- C++ -*-===//
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
/// \file main.cpp
/// \brief The main function of the tests.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/clean_up.h"
#include "ode/common/run_test.h"
#include "ode/common/set_up.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  ode::test::set_up_tests(argc, argv);

  const int result_tests = ode::test::run_tests(argc, argv);

#if ODE_TEST_BENCHMARKING

  ode::test::set_up_benchmarks(argc, argv);

  const int result_benchmarks = ode::test::run_benchmarks(argc, argv);

#endif // ODE_TEST_BENCHMARKING

  ode::test::clean_up();

  return result_tests;
}
