//===---------------------------- main_loop.h -------------------*- C++ -*-===//
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
/// \file main_loop.h
/// \brief Declarations of the game loop functions.
/// \author Antti Kivi
/// \date 3 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_GAME_LOOP_H
#define ODE_FRAMEWORK_GAME_LOOP_H

#include <chrono>

#include "ode/sdl/window_ptr.h"

namespace ode
{
  using namespace std::chrono_literals;

  ///
  /// \brief The time duration between two game ticks.
  ///
  /// The game should run 60 frames a second. Therefore, this is equal to 16 as
  /// 1 / 60 = 0.01666...
  ///
  constexpr auto time_step = 16ms;

  ///
  /// \brief Runs the main loop of the game.
  ///
  /// This function is impure.
  ///
  /// \param window_r pointer to the window.
  ///
  void main_loop(sdl::window_ptr&& window_r);

} // namespace ode

#endif // !ODE_FRAMEWORK_GAME_LOOP_H
