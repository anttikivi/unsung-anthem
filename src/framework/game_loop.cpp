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

#include "scheduler.h"

#include <GLFW/glfw3.h>

namespace anthem
{
  void game_loop(window_ptr&& window)
  {
    using namespace std::chrono_literals;
    using clock = std::chrono::high_resolution_clock;

    logging::trace("Entering the game loop");

    bool quit = false;

    auto delay = 0ns;
    auto t = clock::now();

    game_state current_state{};
    game_state previous_state{};

    while (!quit)
    {
      auto dt = clock::now() - t;
      t = clock::now();
      delay += std::chrono::duration_cast<std::chrono::nanoseconds>(dt);

      logging::trace("The current delay in update time is {}", delay.count());

      while(delay >= time_step)
      {
        delay -= time_step;

        logging::trace("Updating the game state");

        previous_state = std::move(current_state);
        current_state = std::move(update_state(previous_state));

        if (glfwWindowShouldClose(window.get()))
        {
          quit = true;
        }
      }

      const float alpha = static_cast<float>(delay.count()) / time_step.count();
      auto interpolated_state = interpolate_state(
          current_state,
          previous_state,
          alpha);

      // render_state(interpolated_state);

      glfwSwapBuffers(window.get());
      glfwPollEvents();
    }
  }
}
