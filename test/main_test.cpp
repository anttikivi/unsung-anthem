//===------------------------ main_test.cpp ---------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file main_test.cpp
/// \brief The main function of the Unsung Anthem tests.
/// \author Antti Kivi
/// \date 30 June 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "anthem/logging.h"

int main(int argc, const char* argv[])
{
  anthem::logger = anthem::create_logger("test_logger");
  const int result = Catch::Session().run(argc, argv);
  return result < 0xff ? result : 0xff;
}
