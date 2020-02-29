//===------------------------------ set_up.h --------------------*- C++ -*-===//
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
/// \file set_up.h
/// \brief The declarations of the common set up functions of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TEST_COMMON_SET_UP_H
#define ODE_TEST_COMMON_SET_UP_H

namespace ode::test
{
  ///
  /// \brief Sets up the common dependencies of the tests.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return The end code of the program.
  ///
  int set_up_tests(int argc, char* argv[]);

#if ODE_TEST_BENCHMARKING

  ///
  /// \brief Sets up the common dependencies of the benchmarks.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return The end code of the program.
  ///
  int set_up_benchmarks(int argc, char* argv[]);

#endif // ODE_TEST_BENCHMARKING

} // namespace ode::test

#endif // !ODE_TEST_COMMON_SET_UP_H
