//===---------------------------- main_loop.h -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file main_loop.h
/// \brief The declaration of the main loop function.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_MAIN_LOOP_H
#define ODE_FRAMEWORK_MAIN_LOOP_H

#if ODE_STD_CLOCK
# include <chrono>
#endif // ODE_STD_CLOCK

#include "ode/engine_framework.h"
#include "ode/window_t.h"
#include "ode/framework/framework_scene.h"
#include "ode/framework/platform_manager.h"
#include "ode/framework/scheduler.h"

namespace ode
{
#if ODE_STD_CLOCK

  using namespace std::chrono_literals;

#endif // !ODE_STD_CLOCK

  ///
  /// \brief The time duration between two game ticks.
  ///
  /// The game should run 60 frames a second. Therefore, this is equal to 16 as
  /// 1 / 60 = 0.01666...
  ///
#if ODE_STD_CLOCK

  constexpr auto time_step = 16ms;

#else

  constexpr Uint32 time_step = 16;

#endif // !ODE_STD_CLOCK

  ///
  /// \brief Runs the main loop.
  ///
  /// Remarks: This function is impure.
  ///
  /// \tparam A the type of the type of the application implementation.
  ///
  /// \param engine an rvalue reference of the engine framework.
  ///
  template <typename A> void main_loop(engine_framework<A>&& engine)
  {
#if ODE_STD_CLOCK

    using clock = std::chrono::high_resolution_clock;

#endif // ODE_STD_CLOCK

    auto framework = std::move(engine);

    framework_scene current_scene
        = std::move(framework.application().first_scene());

    state current_state{};
    state previous_state{};

#if ODE_STD_CLOCK

    auto delay = 0ns;
    auto t = clock::now();

#else

    Uint32 delay = 0;
    Uint32 t = SDL_GetTicks();

#endif // !ODE_STD_CLOCK

    ODE_TRACE("Entering the main loop");

    while (framework.environment().should_execute())
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

        framework.platform().poll_events(framework.environment());

        ODE_TRACE("Updating the game state");

        previous_state = std::move(current_state);
        current_state = update_state(previous_state, framework);

        framework.state().distribute_state(current_state);

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

      // TODO This is a temporary solution.
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      SDL_GL_SwapWindow(framework.window());

    } // while (!quit)
  }

} // namespace ode

#endif // !ODE_FRAMEWORK_MAIN_LOOP_H
