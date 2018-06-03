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
/// \brief The declaration of the main loop function.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_MAIN_LOOP_H
#define ODE_FRAMEWORK_MAIN_LOOP_H

#if ODE_STD_CLOCK
# include <chrono>
#endif // ODE_STD_CLOCK

#include "ode/window_t.h"

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
  /// \param window_r an rvalue reference of a pointer to the main window.
  ///
  void main_loop(window_t&& window_r);

} // namespace ode

#endif // !ODE_FRAMEWORK_MAIN_LOOP_H
