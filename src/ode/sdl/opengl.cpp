//===----------------------------- opengl.cpp -------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file opengl.cpp
/// \brief The definitions of the utility functions for the Simple DirectMedia
/// Layer OpenGL context.
/// \author Antti Kivi
/// \date 2 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/opengl.h"

#include "ode/logger.h"
#include "ode/gl/gl_config.h"

#include <glad/glad.h>

namespace ode::sdl
{
  SDL_GLContext create_gl_context(window_ptr_t window)
  {
    auto context = SDL_GL_CreateContext(window);

    ODE_TRACE("Created the OpenGL context with SDL");

    SDL_GL_SwapWindow(window);

    ODE_TRACE("Set the window to the OpenGL context");

    gladLoadGLLoader(static_cast<GLADloadproc>(SDL_GL_GetProcAddress));

    ODE_TRACE("Loaded the OpenGL functions");

    SDL_GL_SetSwapInterval(opengl_swap_interval);

    ODE_TRACE("Set the swap interval of OpenGL to {}", opengl_swap_interval);

    return context;
  }
} // namespace ode::sdl
