//===------------------------------ opengl.h --------------------*- C++ -*-===//
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
/// \file opengl.h
/// \brief The declarations of the utility functions for the Simple DirectMedia
/// Layer OpenGL contexts.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_OPENGL_H
#define ODE_SDL_OPENGL_H

#include "ode/sdl/sdl_window_t.h"

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// \brief Initializes a new OpenGL context.
  ///
  /// \param window a pointer to a window.
  ///
  /// \return An object of the type \c SDL_GLContext.
  ///
  SDL_GLContext create_gl_context(window_ptr_t window);

} // namespace ode::sdl

#endif // !ODE_SDL_OPENGL_H
