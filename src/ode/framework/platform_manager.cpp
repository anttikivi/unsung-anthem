//===------------------------ platform_manager.cpp --------------*- C++ -*-===//
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
/// \file platform_manager.cpp
/// \brief The definition of the manager which holds the platform-related
/// utilities.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/framework/platform_manager.h"

#include "ode/logger.h"
#include "ode/framework/environment_manager.h"

#include <SDL2/SDL.h>

namespace ode
{
  void poll_events()
  {
    SDL_Event e;

    while (SDL_PollEvent(&e))
    {
      ODE_TRACE("System event: {}", e.type);

      if (SDL_QUIT == e.type)
      {
        environment.schedule_termination();
      }
    }
  }

} // namespace ode
