//===------------------------- framework.h ----------------------*- C++ -*-===//
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
/// \file framework.h
/// \brief The declarations of the game loop and framework functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_FRAMEWORK_H
#define ANTHEM_FRAMEWORK_H

#include <chrono>

#include "window.h"

namespace anthem
{
  ///
  /// \brief The time duration between two game ticks.
  ///
  /// The game should run 60 frames a second. Therefore, this is equal to 16 as
  /// 1 / 60 = 0.01666...
  ///
  constexpr std::chrono::nanoseconds time_step{std::chrono::milliseconds{16}};

  ///
  /// \brief Runs the main loop of the game.
  ///
  /// This function is impure.
  ///
  /// \param window pointer to the window.
  ///
  void game_loop(window_ptr&& window);

} // namespace anthem

#endif // !ANTHEM_FRAMEWORK_H
