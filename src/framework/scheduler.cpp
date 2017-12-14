//===------------------------ scheduler.cpp ---------------------*- C++ -*-===//
//
//                            Unsung Anthemss
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file scheduler.cpp
/// \brief The definitions of the scheduler functions.
/// \author Antti Kivi
/// \date 10 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "scheduler.h"

#include "anthem/logging.h"

namespace anthem
{
  game_state update_state(const game_state& state)
  {
    logging::trace("Updating the game state");
    return {};
  }

  game_state interpolate_state(
      const game_state& current_state,
      const game_state& previous_state,
      const float alpha)
  {
    logging::trace("The alpha value of the game update time is {}", alpha);

    if (alpha >= 0.5)
    {
      return current_state;
    }
    else
    {
      return previous_state;
    }
  }
}
