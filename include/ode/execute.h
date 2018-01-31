//===-------------------------- execute.h -----------------------*- C++ -*-===//
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
/// \file execute.h
/// \brief The declaration of the main execution function of the game engine.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_EXECUTE_H
#define ODE_EXECUTE_H

#include "ode/args_array.h"

namespace ode
{
  ///
  /// \brief Returns the object of type \c game_state after executing the
  /// program with the given arguments.
  ///
  /// This function is impure.
  ///
  /// TODO Allow adding the custom, game-specific command line options via this
  /// function.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return Does not return anything and, thus, this function is impure.
  ///
  int execute(int argc, args_array argv[]);

  ///
  /// \brief Creates and initializes the managers for the framework.
  ///
  /// This function is impure.
  ///
  /// \return Does not return anything and, thus, this function is impure.
  ///
  void create_managers();

} // namespace ode

#endif // !ODE_EXECUTE_H
