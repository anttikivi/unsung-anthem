//===---------------------------- main_loop.h -------------------*- C++ -*-===//
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
/// \file main_loop.h
/// \brief Declarations of main loop functions of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_MAIN_LOOP_H
#define ODE_MAIN_LOOP_H

#include <chrono>

#include "ode/window_t.h"

namespace ode
{
#ifndef ODE_SDL_TICK_CLOCK

  using namespace std::chrono_literals;

#endif // !defined(ODE_SDL_TICK_CLOCK)

  ///
  /// \brief The time duration between two game ticks.
  ///
  /// The game should run 60 frames a second. Therefore, this is equal to 16 as
  /// 1 / 60 = 0.01666...
  ///
#ifdef ODE_SDL_TICK_CLOCK

  constexpr Uint32 time_step = 16;

#else

  constexpr auto time_step = 16ms;

#endif // !defined(ODE_SDL_TICK_CLOCK)

  ///
  /// \brief Runs the main loop of Obliging Ode.
  ///
  /// This function is impure.
  ///
  /// \param window_r rvalue reference of pointer to main window.
  ///
  void main_loop(window_t&& window_r);

} // namespace ode

#endif // !ODE_MAIN_LOOP_H
