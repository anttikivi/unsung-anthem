//===----------------------------- opengl.cpp -------------------*- C++ -*-===//
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
/// \file opengl.cpp
/// \brief Definitions of utility functions for Simple DirectMedia Layer
/// OpenGL context.
/// \author Antti Kivi
/// \date 2 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/opengl.h"

#include <glad/glad.h>

namespace ode::sdl
{
  SDL_GLContext create_gl_context(SDL_Window* window)
  {
    auto context = SDL_GL_CreateContext(window);

    SDL_GL_SwapWindow(window);
    gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    SDL_GL_SetSwapInterval(1);

    return context;
  }
} // namespace ode::sdl
