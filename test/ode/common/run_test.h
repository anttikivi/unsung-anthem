//===----------------------------- run_test.h -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file run_test.h
/// \brief The declarations of the common running functions of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TEST_COMMON_RUN_TEST_H
#define ODE_TEST_COMMON_RUN_TEST_H

namespace ode::test
{
  ///
  /// \brief Runs the tests.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return The end code of the tests.
  ///
  int run_tests(int argc, char* argv[]);

#if ODE_TEST_BENCHMARKING

  ///
  /// \brief Runs the benchmarks.
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
