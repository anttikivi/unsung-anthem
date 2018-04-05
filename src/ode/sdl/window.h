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
/// \brief Declarations of the window utilities for Simple DirectMedia Layer.
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
  /// \brief Type of objects which hold the information which is used to create
  /// an SDL window.
  ///
  struct window_creation_info final
  {
    ///
    /// \brief The current width of the window.
    ///
    const pixel_count window_width = 0_px;

    ///
    /// \brief The current height of the window.
    ///
    const pixel_count window_height = 0_px;

    ///
    /// \brief The current name of the window.
    ///
    const std::string window_name = "null"s;
  };

  ///
  /// \struct window_info
  /// \brief Type of objects which hold the current information of an SDL
  /// window.
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
  /// \param info the info with which the window is created.
  ///
  /// \return Pointer to the created object of type \c GLFWwindow.
  ///
  window_t create_window(const window_creation_info& info);

} // namespace ode::sdl

#endif // !ODE_SDL_WINDOW_H
