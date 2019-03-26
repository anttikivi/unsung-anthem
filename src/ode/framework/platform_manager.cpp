//===------------------------ platform_manager.cpp --------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file platform_manager.cpp
/// \brief The definition of the manager which holds the platform-related
/// utilities.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/framework/platform_manager.h"

#include "ode/logger.h"

#include <SDL2/SDL.h>

namespace ode
{
  platform_manager::platform_manager(system_t* is) : input_system{is}
  {

  }

  void platform_manager::poll_events(environment_manager& env)
  {
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
      ODE_TRACE("System event: {}", event.type);

      if (SDL_QUIT == event.type)
      {
        env.schedule_termination();
      }
      else
      {
      }
    }
  }

} // namespace ode
