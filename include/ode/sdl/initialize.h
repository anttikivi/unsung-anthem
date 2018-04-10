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
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SDL_INITIALIZE_H
#define ODE_SDL_INITIALIZE_H

#include <stdexcept>

#include "gsl/util"

#include "ode/logger.h"
#include "ode/sdl/version.h"

#include <SDL2/SDL.h>

namespace ode::sdl
{
  ///
  /// \brief Initializes the Simple DirectMedia Layer.
  ///
  /// \return An object of type \c gsl::finally which terminates Simple
  /// DirectMedia Layer.
  ///
  inline auto initialize()
  {
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
      ODE_ERROR("The Simple DirectMedia Layer initialization failed");
      throw std::runtime_error{
          "The Simple DirectMedia Layer initialization failed"};
    }

    ODE_DEBUG("Simple DirectMedia Layer is initialized");

    auto compiled = compiled_version();
    auto linked = linked_version();

    ODE_DEBUG(
        "The program is compiled againts Simple DirectMedia Layer {}.{}.{}",
        compiled.major,
        compiled.minor,
        compiled.patch);
    ODE_DEBUG(
        "The program is linked againts Simple DirectMedia Layer {}.{}.{}",
        linked.major,
        linked.minor,
        linked.patch);

    return gsl::finally([&]()
    {
      SDL_Quit();
      ODE_DEBUG("Simple DirectMedia Layer is terminated");
    });
  }
} // namespace ode::sdl

#endif // !ODE_SDL_INITIALIZE_H
