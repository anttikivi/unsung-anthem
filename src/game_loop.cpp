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
/// \brief The definitions of the game loop functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "game_loop.h"

#include <GLFW/glfw3.h>

namespace anthem
{
  void game_loop(const logging::logger_t& logger, window_ptr&& window)
  {
    using namespace std::chrono_literals;
    using clock = std::chrono::high_resolution_clock;

    logging::trace(logger, "Entering the game loop");

    auto delay{0ns};
    auto time_start{clock::now()};

    bool quit{false};

    while (!quit)
    {
      auto delta_time = clock::now() - time_start;
      time_start = clock::now();
      delay += std::chrono::duration_cast<std::chrono::nanoseconds>(delta_time);

      // update game logic as lag permits
      while(delay >= time_step)
      {
        delay -= time_step;

        // previous_state = current_state;
        // update(&current_state); // update at a fixed rate each time
      }

      // calculate how close or far we are from the next time step
      auto alpha = (float) delay.count() / time_step.count();
      // auto interpolated_state = interpolate(current_state, previous_state, alpha);

      // render(interpolated_state);

      glfwSwapBuffers(window.get());
      glfwPollEvents();

      if (glfwWindowShouldClose(window.get()))
      {
        quit = true;
      }
    }
  }
}
