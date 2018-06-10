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
/// \brief The declaration of the manager which holds platform-related
/// utilities.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_PLATFORM_MANAGER_H
#define ODE_FRAMEWORK_PLATFORM_MANAGER_H

#include <vector>

#include "ode/__config"

// Forward declarations.
namespace ode
{
  class environment_manager;
}

namespace ode
{
  ///
  /// \brief An enumeration type, the enumerators of which represent platforms
  /// on which the program can run.
  ///
  enum class platform
  {
    windows,
    macos,
    linux
  };

  ///
  /// \brief The platform on which the program is currently running.
  ///
#if ODE_WINDOWS
  constexpr platform current_platform = platform::windows;
#elif ODE_MACOS
  constexpr platform current_platform = platform::macos;
#else
  constexpr platform current_platform = platform::linux;
#endif // !ODE_WINDOWS && !ODE_MACOS

  ///
  /// \brief Polls all of the current system events waiting and forwards them.
  ///
  /// Remarks: The reference to the engine which is passed to the function is
  /// not constant and, thus, modifies the original engine object.
  ///
  /// \param e a reference to the application engine.
  ///
  void poll_events(environment_manager& env);

} // namespace ode

#endif // !ODE_FRAMEWORK_PLATFORM_MANAGER_H
