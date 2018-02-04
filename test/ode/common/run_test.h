//===------------------------------- run.h ----------------------*- C++ -*-===//
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
/// \file run.h
/// \brief Declaration of the common running function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TEST_COMMON_RUN_TEST_H
#define ODE_TEST_COMMON_RUN_TEST_H

namespace ode
{
  namespace test
  {
    ///
    /// \brief Runs the tests and benchmarks.
    ///
    /// \param argc the number of arguments passed in the execution.
    /// \param argv array containing the arguments passed in the execution.
    ///
    /// \return The end code of the tests.
    ///
    int run(int argc, char* argv[]);

  } // namespace test
} // namespace ode

#endif // !ODE_TEST_COMMON_RUN_TEST_H
