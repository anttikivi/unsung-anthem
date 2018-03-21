//===------------------------------ set_up.h --------------------*- C++ -*-===//
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
/// \file set_up.h
/// \brief Declaration of the common set up function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
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
  int set_up(int argc, char* argv[]);

} // namespace ode::test

#endif // !ODE_TEST_COMMON_SET_UP_H
