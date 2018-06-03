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
/// \brief The declaration and definition of the main function of the program.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/run.h"

#include <SDL2/SDL.h>

///
/// \brief Returns the execution status of the program with the arguments
/// passed in.
///
/// \param argc the number of arguments passed in the execution.
/// \param argv the array containing the arguments passed in the execution.
///
/// \return The end code of the program.
///
int main(int argc, ode::argv_t argv[])
{
  const int r = anthem::run(argc, argv);
  return r;
}
