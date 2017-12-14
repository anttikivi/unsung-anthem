//===------------------------- game_loop.h ----------------------*- C++ -*-===//
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
/// \file game_loop.h
/// \brief The declarations of the game loop functions.
/// \author Antti Kivi
/// \date 10 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_FRAMEWORK_GAME_LOOP_H
#define ANTHEM_FRAMEWORK_GAME_LOOP_H

#include <chrono>

#include "../manager/state.h"
#include "../window.h"

namespace anthem
{
  struct arguments;
}

namespace anthem
{
  ///
  /// \brief The time duration between two game ticks.
  ///
  /// The game should run 60 frames a second. Therefore, this is equal to 16 as
  /// 1 / 60 = 0.01666...
  ///
  constexpr std::chrono::milliseconds time_step{std::chrono::milliseconds{16}};

  ///
  /// \brief Runs the main loop of the game.
  ///
  /// This function is impure.
  ///
  /// \param args_r the parsed command line arguments.
  /// \param window_r pointer to the window.
  ///
  void game_loop(arguments&& args_r, window_ptr&& window_r);

} // namespace anthem

#endif // !ANTHEM_FRAMEWORK_GAME_LOOP_H
