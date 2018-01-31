//===------------------------- window.cpp ------------------------*- C++ -*-===//
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
/// \file window.cpp
/// \brief The definition of the window-related functions.
/// \author Antti Kivi
/// \date 25 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "window.h"

#include "anthem/logger.h"

#include "arguments.h"

namespace anthem
{
  window_ptr create_window(const arguments& args)
  {
      SDL_GL_SetAttribute(
          SDL_GL_CONTEXT_PROFILE_MASK,
          SDL_GL_CONTEXT_PROFILE_CORE);
      SDL_GL_SetAttribute(
          SDL_GL_CONTEXT_MAJOR_VERSION,
          ANTHEM_OPENGL_VERSION_MAJOR);
	    SDL_GL_SetAttribute(
          SDL_GL_CONTEXT_MINOR_VERSION,
          ANTHEM_OPENGL_VERSION_MINOR);

      // MacOS only supports forward-compatible core contexts.
#if __APPLE__
      // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
#endif // __APPLE__

      ANTHEM_TRACE(
          "Set the OpenGL version hint for the window to {}.{}",
          ANTHEM_OPENGL_VERSION_MAJOR,
          ANTHEM_OPENGL_VERSION_MINOR);

      window_ptr window{
          SDL_CreateWindow(
              args.window_name.c_str(),
              SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED,
              args.window_width,
              args.window_height,
              SDL_WINDOW_OPENGL),
          &SDL_DestroyWindow};

      if (!window)
      {
        ANTHEM_ERROR("The Simple DirectMedia Layer window creation failed");
        return {nullptr, nullptr};
      }

      return window;
    }

} // namespace anthem
