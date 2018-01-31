//===--------------------------- sdl.cpp ------------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file sdl.cpp
/// \brief The definitions of the initializing Simple DirectMedia Layer
/// functions.
/// \author Antti Kivi
/// \date 10 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "sdl.h"

#include <glad/glad.h>

namespace anthem
{
  SDL_GLContext create_gl_context(SDL_Window* window)
  {
    auto context = SDL_GL_CreateContext(window);

    SDL_GL_SwapWindow(window);
    gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress));
    SDL_GL_SetSwapInterval(1);

    return context;
  }
} // namespace anthem
