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

#include "ode/common/clean_up.h"
#include "ode/common/run_test.h"
#include "ode/common/set_up.h"

#include "anthem/logger.h"

#include "anthem/logging_config.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  anthem::logger = ode::create_logger(
      "anthem_test_logger",
      anthem::logger_pattern,
      anthem::logger_level);
  ode::test::set_up();
  const int result = ode::test::run(argc, argv);
  ode::test::clean_up();
  return result < 0xff ? result : 0xff;
}
