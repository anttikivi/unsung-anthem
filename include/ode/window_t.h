//===----------------------------- window_t.h -------------------*- C++ -*-===//
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
/// \file window_t.h
/// \brief Declarations of window types of Obliging Ode.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_WINDOW_T_H
#define ODE_WINDOW_T_H

#include "ode/sdl/window_t.h"

namespace ode
{
  ///
  /// \brief Type of pointers to the window object.
  ///
  using window_t = sdl::window_t;

  ///
  /// \brief Pointer type which is used as parameter for passing the raw window
  /// pointer.
  ///
  using window_ptr_t = sdl::window_ptr_t;

} // namespace ode

#endif // !ODE_WINDOW_T_H
