//===----------------------------- window_t.h -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file window_t.h
/// \brief The declarations of the window types.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_WINDOW_T_H
#define ODE_WINDOW_T_H

#include "ode/sdl/sdl_window_t.h"

namespace ode
{
  ///
  /// \brief The type of the window object.
  ///
  using window_t = sdl::window_t;

  ///
  /// \brief A pointer type which is used as the parameter type for raw window
  /// pointers.
  ///
  using window_ptr_t = sdl::window_ptr_t;

} // namespace ode

#endif // !ODE_WINDOW_T_H
