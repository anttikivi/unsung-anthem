//===------------------------------ main.cpp --------------------*- C++ -*-===//
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
/// \file main.cpp
/// \brief The main function of the Unsung Anthem tests.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#define CATCH_CONFIG_RUNNER

#include "catch.hpp"

#include "ode/logger.h"

#include "anthem/logger.h"

#include "anthem/logging_config.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  anthem::logger = ode::create_logger(
      "anthem_test_logger",
      anthem::logger_pattern,
      anthem::logger_level);
  ode::logger = ode::create_logger("ode_test_logger");
  const int result = Catch::Session().run(argc, argv);
  return result < 0xff ? result : 0xff;
}
