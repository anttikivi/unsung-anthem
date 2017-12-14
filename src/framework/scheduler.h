//===------------------------- scheduler.h ----------------------*- C++ -*-===//
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
/// \file scheduler.h
/// \brief The declarations of the scheduler functions.
/// \author Antti Kivi
/// \date 10 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_FRAMEWORK_SCHEDULER_H
#define ANTHEM_FRAMEWORK_SCHEDULER_H

namespace anthem
{
  struct game_state;
}

namespace anthem
{
  ///
  /// \brief Runs a single tick of the game.
  ///
  /// \param state the last game state.
  ///
  /// \return The new game state.
  ///
  game_state update_state(const game_state& state);

  ///
  /// \brief Calculates the state which is in the middle of the two states at
  /// the alpha point given.
  ///
  /// \param current_state the current game state.
  /// \param previous_state the previous game state.
  /// \param alpha the value denoting how to close the game is to the next
  /// state.
  ///
  /// \return The interpolated game state.
  ///
  game_state interpolate_state(
      const game_state& current_state,
      const game_state& previous_state,
      const float alpha);

} // namespace anthem

#endif // !ANTHEM_FRAMEWORK_SCHEDULER_H
