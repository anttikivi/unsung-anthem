/// The declarations of the window types for Simple DirectMedia Layer.
/// \file
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SDL_SDL_WINDOW_T_H
#define ODE_SDL_SDL_WINDOW_T_H

#include <memory>

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// The type of the window objects.
  ///
  using window_t = std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>;

  ///
  /// A pointer type which is used as the parameter type for raw window
  /// pointers.
  ///
  using window_ptr_t = SDL_Window*;

} // namespace ode::sdl

#endif // !ODE_SDL_SDL_WINDOW_T_H
