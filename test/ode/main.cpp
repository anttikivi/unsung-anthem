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
/// \brief The main function of the Obliging Ode tests.
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

#include "logging_config.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  ode::logger = ode::create_logger(
      "ode_test_logger",
      ode::logger_pattern,
      ode::logger_level);
  const int result = Catch::Session().run(argc, argv);
  return result < 0xff ? result : 0xff;
}
