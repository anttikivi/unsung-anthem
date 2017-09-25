//===------------------------ game_state.cpp --------------------*- C++ -*-===//
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
/// \file game_state.cpp
/// \brief The definitions of the state-related types and functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "game_state.h"

#include <string>

namespace anthem
{
  game_state update_state(
      const logging::logger_t& logger,
      const game_state& state)
  {
    logging::trace(logger, "Updating the game state");
    return {};
  }

  game_state interpolate_state(
      const logging::logger_t& logger,
      const game_state& current_state,
      const game_state& previous_state,
      const float alpha)
  {
    logging::trace(logger, "The alpha value of the game update time is {}", std::to_string(alpha));
    if (alpha >= 0.5)
    {
      return current_state;
    }
    else
    {
      return previous_state;
    }
  }

} // namespace anthem
