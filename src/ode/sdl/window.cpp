//===----------------------------- window.cpp -------------------*- C++ -*-===//
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
/// \file window.cpp
/// \brief Definitions of the window utilities for Simple DirectMedia Layer.
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/window.h"

#include <stdexcept>

#include "ode/logger.h"

#include "ode/config.h"

namespace ode::sdl
{
  window_t create_window(const window_creation_info& info)
  {
      SDL_GL_SetAttribute(
          SDL_GL_CONTEXT_PROFILE_MASK,
          SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, opengl_version_major);
	    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, opengl_version_minor);
	    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
      // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

#if ODE_OPENGL_SDL_ACCELERATED_VISUAL
      SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
#endif // ODE_OPENGL_SDL_ACCELERATED_VISUAL

      // MacOS only supports forward-compatible core contexts.
#if __APPLE__

      SDL_GL_SetAttribute(
          SDL_GL_CONTEXT_FLAGS,
          SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);

#endif // __APPLE__

      ODE_TRACE(
          "Set the OpenGL version hint for the window to {}.{}",
          opengl_version_major,
          opengl_version_minor);

      window_t window = {
          SDL_CreateWindow(
              info.window_name.data(),
              SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED,
              info.window_width,
              info.window_height,
              SDL_WINDOW_OPENGL),
          &SDL_DestroyWindow};

      if (!window)
      {
        ODE_ERROR("The Simple DirectMedia Layer window creation failed");
        const std::string error = std::string{SDL_GetError()};
        throw std::runtime_error{
            std::string{
                "The Simple DirectMedia Layer window creation failed, '"}
            + error
            + "'"};
      }

      return window;
    }

} // namespace ode::sdl
