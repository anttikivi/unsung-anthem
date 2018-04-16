//===----------------------------- platform.h -------------------*- C++ -*-===//
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
/// \file platform.h
/// \brief Declarations of platform-related utilities of Obliging Ode.
/// \author Antti Kivi
/// \date 16 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_PLATFORM_H
#define ODE_PLATFORM_H

#include "ode/__config"

namespace ode
{
  ///
  /// \brief An enumeration type, enumerators of which represent platforms on
  /// which Obliging Ode can run.
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

} // namespace ode

#endif // !ODE_PLATFORM_H
