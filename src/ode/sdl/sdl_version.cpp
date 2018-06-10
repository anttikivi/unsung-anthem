//===-------------------------- sdl_version.cpp -----------------*- C++ -*-===//
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
/// \file sdl_version.cpp
/// \brief The definitions of the Simple DirectMedia Layer version utility
/// functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

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
