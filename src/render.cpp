//===------------------------- render.cpp -----------------------*- C++ -*-===//
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
/// \file render.cpp
/// \brief The definitions of the rendering-related functions.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "render.h"

#include "game_state.h"

namespace anthem
{
  void render_state(const logger_t& logger, const game_state& state)
  {
    logging::trace(logger, "Rendering a game state");
  }
} // namespace anthem
