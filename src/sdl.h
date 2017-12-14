//===---------------------------- sdl.h -------------------------*- C++ -*-===//
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
/// \file sdl.h
/// \brief The declarations of the initializing Simple DirectMedia Layer
/// functions.
/// \author Antti Kivi
/// \date 10 December 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_SDL_H
#define ANTHEM_SDL_H

#include "gsl/util"

#include "anthem/logging.h"

#include <SDL2/SDL.h>

namespace anthem
{

  ///
  /// \brief Initializes the Simple DirectMedia Layer framework.
  ///
  /// \return An object of type \c gsl::final_action containing a function
  /// which terminates Simple DirectMedia Layer.
  ///
  inline auto initialize_sdl()
  {
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
      logging::error("The Simple DirectMedia Layer initialization failed");
    }

    logging::debug("Simple DirectMedia Layer is initialized");

    return gsl::finally([&]()
    {
      SDL_Quit();
      logging::debug("Simple DirectMedia Layer is terminated");
    });
  }

  ///
  /// \brief Initializes a new Simple DirectMedia Layer object representing
  /// the OpenGL context.
  ///
  /// \param window a pointer to the game window.
  ///
  /// \return The object of type \c SDL_GLContext.
  ///
  SDL_GLContext create_gl_context(SDL_Window* window);

} // namespace anthem

#endif // !ANTHEM_SDL_H
