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
/// \brief The definitions of the main loop functions.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/framework/main_loop.h"

#include <type_traits>

#include "ode/logger.h"
#include "ode/framework/environment_manager.h"
#include "ode/framework/platform_manager.h"

#include <glad/glad.h>

#include <SDL2/SDL.h>

namespace ode
{
  void main_loop(window_t&& window_r)
  {
#if ODE_STD_CLOCK

    using clock = std::chrono::high_resolution_clock;

#endif // ODE_STD_CLOCK

    window_t window = std::move(window_r);

    ODE_TRACE("Entering the game loop");

#if ODE_STD_CLOCK

    auto delay = 0ns;
    auto t = clock::now();

#else

    Uint32 delay = 0;
    Uint32 t = SDL_GetTicks();

#endif // !ODE_STD_CLOCK

    SDL_Event event;

    while (environment.should_execute())
    {
#if ODE_STD_CLOCK

      auto dt = clock::now() - t;
      t = clock::now();
      delay += std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

# if !ODE_PRINT_LOOP_MILLISECONDS

      ODE_TRACE("The current delay in update time is {}", delay.count());

# else

      ODE_TRACE(
          "The current delay in update time is {}",
          std::chrono::duration_cast<std::chrono::milliseconds>(
              delay).count());

# endif // ODE_PRINT_LOOP_NANOSECONDS

#else

      Uint32 dt = SDL_GetTicks() - t;
      t = SDL_GetTicks();
      delay += dt;

      ODE_TRACE("The current delay in update time is {}", delay);

#endif // !ODE_STD_CLOCK

      while (delay >= time_step)
      {
        delay -= time_step;

        poll_events();

        ODE_TRACE("Updating the game state");

        // previous_state = std::move(current_state);
        // current_state = update_state(previous_state);

      } // while (delay >= time_step)

#if ODE_STD_CLOCK

      using ms = std::chrono::milliseconds;

      const float alpha
          = static_cast<float>(std::chrono::duration_cast<ms>(delay).count())
              / time_step.count();

#else

      const float alpha = static_cast<float>(delay) / time_step;

#endif // !ODE_STD_CLOCK

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
