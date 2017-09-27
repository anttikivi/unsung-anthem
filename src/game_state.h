//===------------------------ game_state.h ----------------------*- C++ -*-===//
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
/// \file game_state.h
/// \brief The declarations of the state-related types and functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_GAME_STATE_H
#define ANTHEM_GAME_STATE_H

namespace anthem
{
  ///
  /// \struct game_state
  /// \brief Type of objects which represent a state of the game.
  ///
  struct game_state final
  {
    ///
    /// \brief Whether or not the game ought to be quit.
    ///
    bool should_quit = false;
  };

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

#endif // !ANTHEM_GAME_STATE_H
