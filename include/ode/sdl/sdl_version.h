/// The declarations of the Simple DirectMedia Layer version utility functions.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SDL_SDL_VERSION_H
#define ODE_SDL_SDL_VERSION_H

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// Gets an object of the type \c SDL_version which represents the version of
  /// the Simple DirectMedia Layer against which the program was compiled.
  ///
  /// \return An object of the type \c SDL_version.
  ///
  SDL_version compiled_version();

  ///
  /// Gets an object of the type \c SDL_version which represents the version of
  /// the Simple DirectMedia Layer against which the program is currently
  /// linked.
  ///
  /// \return An object of the type \c SDL_version.
  ///
  SDL_version linked_version();

} // namespace ode::sdl

#endif // !ODE_SDL_SDL_VERSION_H
