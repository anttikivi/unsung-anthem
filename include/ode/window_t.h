/// The declarations of the window types.
/// \file
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_WINDOW_T_H
#define ODE_WINDOW_T_H

#include "ode/sdl/sdl_window_t.h"

namespace ode
{
  ///
  /// The type of the window object.
  ///
  using window_t = sdl::window_t;

  ///
  /// A pointer type which is used as the parameter type for raw window
  /// pointers.
  ///
  using window_ptr_t = sdl::window_ptr_t;

} // namespace ode

#endif // !ODE_WINDOW_T_H
