/// The declarations of the common running functions of the tests.
/// \file
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_TEST_COMMON_RUN_TEST_H
#define ODE_TEST_COMMON_RUN_TEST_H

namespace ode::test
{
  ///
  /// Runs the tests.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return The end code of the tests.
  ///
  int run_tests(int argc, char* argv[]);

#if ODE_TEST_BENCHMARKING

  ///
  /// Runs the benchmarks.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return The end code of the tests.
  ///
  int run_benchmarks(int argc, char* argv[]);

#endif // ODE_TEST_BENCHMARKING

} // namespace ode::test

#endif // !ODE_TEST_COMMON_RUN_TEST_H
