//===---------------------------- run_test.cpp ------------------*- C++ -*-===//
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
/// \file run_test.cpp
/// \brief Definition of the common running function of the tests.
/// \author Antti Kivi
/// \date 4 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/run_test.h"

#define CATCH_CONFIG_RUNNER

#include <catch.hpp>

#include <hayai/hayai.hpp>

namespace ode
{
  namespace test
  {
    int run(int argc, char* argv[])
    {
      const int result = Catch::Session().run(argc, argv);

      hayai::ConsoleOutputter console_outputter;
 
      hayai::Benchmarker::AddOutputter(console_outputter);
      hayai::Benchmarker::RunAllTests();

      return result;
    }
  } // namespace test
} // namespace ode
