//===------------------------------ window.h --------------------*- C++ -*-===//
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
/// \file window.h
/// \brief The declarations of the window utilities for Simple DirectMedia
/// Layer.
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_WINDOW_H
#define ODE_SDL_WINDOW_H

#include <string>

#include "ode/pixel_count.h"
#include "ode/sdl/window_t.h"

namespace ode::sdl
{
  using namespace std::literals::string_literals;

  ///
  /// \struct window_info
  /// \brief The type of the objects which hold the data which are used to
  /// create a Simple DirectMedia Layer window.
  ///
  struct window_creation_info final
  {
    ///
    /// \brief The initial width of the window.
    ///
    const pixel_count window_width = 0_px;

    ///
    /// \brief The initial height of the window.
    ///
    const pixel_count window_height = 0_px;

    ///
    /// \brief The initial name of the window.
    ///
    const std::string window_name = "null"s;
  };

  ///
  /// \struct window_info
  /// \brief The type of the objects which hold the data of a Simple
  /// DirectMedia Layer window.
  ///
  /// TODO
  ///
  struct window_info final
  {
  };

  ///
  /// \brief Initializes a new Simple DirectMedia Layer window with an OpenGL
  /// context.
  ///
  /// \param info the data with which the window is created.
  ///
  /// \return A pointer to the created window object.
  ///
  window_t create_window(const window_creation_info& info);

} // namespace ode::sdl

#endif // !ODE_SDL_WINDOW_H
