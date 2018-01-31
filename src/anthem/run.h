//===---------------------------- run.h -------------------------*- C++ -*-===//
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
/// \file run.h
/// \brief The declaration of the main execution function of the game.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_RUN_H
#define ANTHEM_RUN_H

#include "ode/args_array.h"

namespace anthem
{
  ///
  /// \brief Returns the object of type \c game_state after executing the
  /// program with the given arguments.
  ///
  /// This function is impure.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return Does not return anything and, thus, this function is impure.
  ///
  int run(int argc, ode::args_array argv[]);

} // namespace anthem

#endif // !ANTHEM_RUN_H
