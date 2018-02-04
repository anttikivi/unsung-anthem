//===------------------------------ run.cpp ---------------------*- C++ -*-===//
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
/// \file run.cpp
/// \brief Definition of the common running function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "run_test.h"

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

namespace ode
{
  namespace test
  {
    int run(int argc, char* argv[])
    {
      const int result = Catch::Session().run(argc, argv);
      return result;
    }
  } // namespace test
} // namespace ode
