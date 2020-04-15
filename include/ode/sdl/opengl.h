/// The declarations of the utility functions for the Simple DirectMedia Layer
/// OpenGL contexts.
/// \file
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SDL_OPENGL_H
#define ODE_SDL_OPENGL_H

#include <SDL2/SDL.h>

#include "ode/sdl/sdl_window_t.h"

namespace ode::sdl
{
  ///
  /// Initializes a new OpenGL context.
  ///
  /// \param window a pointer to a window.
  ///
  /// \return An object of the type \c SDL_GLContext.
  ///
  SDL_GLContext create_gl_context(window_ptr_t window);

} // namespace ode::sdl

#endif // !ODE_SDL_OPENGL_H
