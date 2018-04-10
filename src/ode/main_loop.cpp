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
/// \brief Definitions of main loop functions of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/main_loop.h"

#include <type_traits>

#include "ode/logger.h"

#include <glad/glad.h>

#include <SDL2/SDL.h>

namespace ode
{
  void main_loop(window_t&& window_r)
  {
#ifndef ODE_SDL_TICK_CLOCK

    using clock = std::chrono::high_resolution_clock;

#endif // !defined(ODE_SDL_TICK_CLOCK)

    window_t window = std::move(window_r);

    ODE_TRACE("Entering the game loop");

    bool quit = false;

#ifdef ODE_SDL_TICK_CLOCK

    Uint32 delay = 0;
    Uint32 t = SDL_GetTicks();

#else

    auto delay = 0ns;
    auto t = clock::now();

#endif // !defined(ODE_SDL_TICK_CLOCK)

    SDL_Event event;

    while (!quit)
    {
#ifdef ODE_SDL_TICK_CLOCK

      Uint32 dt = SDL_GetTicks() - t;
      t = SDL_GetTicks();
      delay += dt;

      ODE_TRACE("The current delay in update time is {}", delay);

#else

      auto dt = clock::now() - t;
      t = clock::now();
      delay += std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

# ifndef ODE_PRINT_LOOP_MILLISECONDS

      ODE_TRACE("The current delay in update time is {}", delay.count());

# else

      ODE_TRACE(
          "The current delay in update time is {}",
          std::chrono::duration_cast<std::chrono::milliseconds>(
              delay).count());

# endif // defined(ODE_PRINT_LOOP_NANOSECONDS)

#endif // !defined(ODE_SDL_TICK_CLOCK)

      while (delay >= time_step)
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

      } // while (delay >= time_step)

#ifdef ODE_SDL_TICK_CLOCK

      const float alpha = static_cast<float>(delay) / time_step;

#else

      using ms = std::chrono::milliseconds;

      const float alpha
          = static_cast<float>(std::chrono::duration_cast<ms>(delay).count())
              / time_step.count();

#endif // !defined(ODE_SDL_TICK_CLOCK)

      ODE_TRACE(
          "The alpha value for state-rendering interpolation is {}",
          alpha);
      // auto interpolated_state = interpolate_state(
      //     current_state,
      //     previous_state,
      //     alpha);

      // render_state(interpolated_state);

      // TODO This is a temporary solution
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      SDL_GL_SwapWindow(window.get());

    } // while (!quit)
  }
} // namespace ode
