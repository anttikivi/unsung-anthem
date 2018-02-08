//===----------------------------- clean_up.h -------------------*- C++ -*-===//
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
/// \file clean_up.h
/// \brief Declaration of the common cleanup function of the tests.
/// \author Antti Kivi
/// \date 8 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_TEST_COMMON_CLEAN_UP_H
#define ODE_TEST_COMMON_CLEAN_UP_H

namespace ode
{
  namespace test
  {
    ///
    /// \brief Cleans up the tests.
    ///
    void clean_up();

  } // namespace test
} // namespace ode

#endif // !ODE_TEST_COMMON_CLEAN_UP_H