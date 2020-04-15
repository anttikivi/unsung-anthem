/// The main function of the tests.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include <SDL2/SDL.h>

#include "ode/common/clean_up.h"
#include "ode/common/run_test.h"
#include "ode/common/set_up.h"

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
