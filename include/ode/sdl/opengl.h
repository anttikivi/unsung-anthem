//===------------------------------ opengl.h --------------------*- C++ -*-===//
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
/// \file opengl.h
/// \brief Declarations of utility functions for Simple DirectMedia Layer
/// OpenGL context.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_OPENGL_H
#define ODE_SDL_OPENGL_H

#include "ode/sdl/window_t.h"

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// \brief Initializes a new OpenGL context.
  ///
  /// \param window a pointer to a window.
  ///
  /// \return The object of type \c SDL_GLContext.
  ///
  SDL_GLContext create_gl_context(window_ptr_t window);

} // namespace ode::sdl

#endif // !ODE_SDL_OPENGL_H
