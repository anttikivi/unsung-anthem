//===------------------------- platform_manager.h ---------------*- C++ -*-===//
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
/// \file platform_manager.h
/// \brief Declaration of manager which holds platform-related utilities of
/// Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_PLATFORM_MANAGER_H
#define ODE_PLATFORM_MANAGER_H

#include <vector>

#include "ode/__config"
#include "ode/event_t.h"

namespace ode
{
  ///
  /// \brief An enumeration type, the enumerators of which represent platforms
  /// on which Obliging Ode can run.
  ///
  enum class platform
  {
    windows,
    macos,
    linux
  };

  ///
  /// \brief Platform on which Obliging Ode is currently running.
  ///
#if ODE_WINDOWS
  constexpr platform current_platform = platform::windows;
#elif ODE_MACOS
  constexpr platform current_platform = platform::macos;
#else
  constexpr platform current_platform = platform::linux;
#endif // !ODE_WINDOWS && !ODE_MACOS

  ///
  /// \brief Polls all of the current system events waiting, removes them from
  /// the queue, and returns them.
  ///
  /// \return An object of type \c std::vector which holds objects of type
  /// \c event_t.
  ///
  std::vector<event_t> poll_events();

} // namespace ode

#endif // !ODE_PLATFORM_MANAGER_H
