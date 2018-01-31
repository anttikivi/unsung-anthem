//===------------------------ main_test.cpp ---------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2018 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file main_test.cpp
/// \brief The main function of the Ode tests.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

// #include "anthem/logger.h"

// #include "logging_config.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  /*
  anthem::logger = anthem::create_logger(
      "test_logger",
      anthem::logger_pattern,
      anthem::logger_level);
  */
  const int result = Catch::Session().run(argc, argv);
  return result < 0xff ? result : 0xff;
}
