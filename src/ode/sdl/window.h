/// The declarations of the window utilities for Simple DirectMedia Layer.
/// \file
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SDL_WINDOW_H
#define ODE_SDL_WINDOW_H

#include <string>

#include "ode/pixel_t.h"
#include "ode/sdl/sdl_window_t.h"

namespace ode::sdl
{
  using namespace std::literals::string_literals;
  using namespace literals::number_literals;

  ///
  /// The type of the objects which hold the data which are used to create a
  /// Simple DirectMedia Layer window.
  ///
  struct window_creation_info final
  {
    ///
    /// The initial width of the window.
    ///
    const pixel_t window_width = 0_px;

    ///
    /// The initial height of the window.
    ///
    const pixel_t window_height = 0_px;

    ///
    /// The initial name of the window.
    ///
    const std::string window_name = "null"s;
  };

  ///
  /// The type of the objects which hold the data of a Simple DirectMedia Layer
  /// window.
  ///
  /// TODO
  ///
  struct window_info final
  {
  };

  ///
  /// Initializes a new Simple DirectMedia Layer window with an OpenGL context.
  ///
  /// \param info the data with which the window is created.
  ///
  /// \return A pointer to the created window object.
  ///
  window_t create_window(const window_creation_info& info);

} // namespace ode::sdl

#endif // !ODE_SDL_WINDOW_H
