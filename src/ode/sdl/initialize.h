//===---------------------------- initialize.h ------------------*- C++ -*-===//
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
/// \file initialize.h
/// \brief Declarations of the initialization utility function for Simple
/// DirectMedia Layer.
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_INITIALIZE_H
#define ODE_SDL_INITIALIZE_H

#include "gsl/util"

#include "ode/logger.h"

#include <SDL2/SDL.h>

namespace ode::sdl
{

  inline auto initialize()
  {
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
      ODE_ERROR("The Simple DirectMedia Layer initialization failed");
    }

    ODE_DEBUG("Simple DirectMedia Layer is initialized");

    return gsl::finally([&]()
    {
      SDL_Quit();
      ODE_DEBUG("Simple DirectMedia Layer is terminated");
    });
  }

} // namespace ode::sdl

#endif // !ODE_SDL_INITIALIZE_H
