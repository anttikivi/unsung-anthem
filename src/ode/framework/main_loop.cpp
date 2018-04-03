//===--------------------------- main_loop.cpp ------------------*- C++ -*-===//
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
/// \file main_loop.cpp
/// \brief Definitions of the main loop functions.
/// \author Antti Kivi
/// \date 3 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/framework/main_loop.h"

#include <type_traits>

#include "ode/logger.h"

#include <SDL2/SDL.h>

namespace ode
{
  void main_loop(sdl::window_ptr&& window_r)
  {
    using clock = std::chrono::high_resolution_clock;

    // arguments args = std::move(args_r);
    sdl::window_ptr window = std::move(window_r);

    ODE_TRACE("Entering the game loop");

    bool quit = false;

    auto delay = 0ns;
    auto t = clock::now();

    SDL_Event event;

    while (!quit)
    {
      auto dt = clock::now() - t;
      t = clock::now();
      delay += std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

      ODE_TRACE("The current delay in update time is {}", delay.count());

      while(delay >= time_step)
      {
        delay -= time_step;

        while (SDL_PollEvent(&event))
        {
          if (event.type == SDL_QUIT)
          {
            quit = true;
          }
        }

        ODE_TRACE("Updating the game state");

        // previous_state = std::move(current_state);
        // current_state = update_state(previous_state);
      }

      using ms = std::chrono::milliseconds;

      const float alpha
          = static_cast<float>(std::chrono::duration_cast<ms>(delay).count())
              / time_step.count();

      ODE_TRACE(
          "The alpha value for state-rendering interpolation is {}",
          alpha);
      // auto interpolated_state = interpolate_state(
      //     current_state,
      //     previous_state,
      //     alpha);

      // render_state(interpolated_state);

      SDL_GL_SwapWindow(window.get());
    }
  }
}
