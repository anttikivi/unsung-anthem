//===------------------------ game_loop.cpp ---------------------*- C++ -*-===//
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
/// \file game_loop.cpp
/// \brief The definitions of the game loop and scheduler functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "game_loop.h"

#include <type_traits>

#include "anthem/logging.h"

#include "../arguments.h"
#include "../manager/game_state.h"
#include "scheduler.h"

#include <SDL2/SDL.h>

namespace anthem
{
  void game_loop(arguments&& args_r, window_ptr&& window_r)
  {
    using clock = std::chrono::high_resolution_clock;

    arguments args = std::move(args_r);
    window_ptr window = std::move(window_r);

    logging::trace("Entering the game loop");

    bool quit = false;

    auto delay = 0ns;
    auto t = clock::now();

    game_state current_state{};
    game_state previous_state{};

    SDL_Event event;

    while (!quit)
    {
      auto dt = clock::now() - t;
      t = clock::now();
      delay += std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

      logging::trace("The current delay in update time is {}", delay.count());

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

        logging::trace("Updating the game state");

        previous_state = std::move(current_state);
        current_state = std::move(update_state(previous_state));
      }

      const float alpha = static_cast<float>(delay.count()) / time_step.count();
      auto interpolated_state = interpolate_state(
          current_state,
          previous_state,
          alpha);

      // render_state(interpolated_state);

      SDL_GL_SwapWindow(window.get());
    }
  }
}
