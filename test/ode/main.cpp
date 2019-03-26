//===------------------------------ main.cpp --------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file main.cpp
/// \brief The main function of the tests.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/common/clean_up.h"
#include "ode/common/run_test.h"
#include "ode/common/set_up.h"

#include <SDL2/SDL.h>

int main(int argc, char* argv[])
{
  ode::test::set_up(argc, argv);
  const int result = ode::test::run(argc, argv);
  ode::test::clean_up();
  return result;
}
