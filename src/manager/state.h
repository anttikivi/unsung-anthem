//===--------------------------- state.h ------------------------*- C++ -*-===//
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
/// \file state.h
/// \brief Declaration of game framework state manager.
/// \author Antti Kivi
/// \date 5 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_MANAGER_STATE_H
#define ANTHEM_MANAGER_STATE_H

#include <vector>

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
} // namespace anthem

#endif // !ANTHEM_MANAGER_STATE_H
