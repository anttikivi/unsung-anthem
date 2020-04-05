/// The definitions of the Simple DirectMedia Layer version utility functions.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/sdl/sdl_version.h"

#include "ode/logger.h"

namespace ode::sdl
{
  SDL_version compiled_version()
  {
    SDL_version v;
    SDL_VERSION(&v);
    ODE_TRACE("Got the compiled version of Simple DirectMedia Layer");
    return v;
  }

  SDL_version linked_version()
  {
    SDL_version v;
    SDL_GetVersion(&v);
    ODE_TRACE("Got the linked version of Simple DirectMedia Layer");
    return v;
  }

} // namespace ode::sdl
