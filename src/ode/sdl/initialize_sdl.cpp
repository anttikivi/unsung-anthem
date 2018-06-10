//===-------------------------- initialize_sdl.h ----------------*- C++ -*-===//
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
/// \file initialize_sdl.h
/// \brief The definition of the initialization utility function for Simple
/// DirectMedia Layer.
/// \author Antti Kivi
/// \date 6 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/initialize_sdl.h"

#include <stdexcept>

#include "ode/logger.h"
#include "ode/sdl/sdl_version.h"

#include <SDL2/SDL.h>

namespace ode::sdl
{
  void initialize()
  {
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
      ODE_ERROR("The Simple DirectMedia Layer initialization failed");
      const std::string error = std::string{SDL_GetError()};
      throw std::runtime_error{
          std::string{"The Simple DirectMedia Layer initialization failed, '"}
          + error
          + "'"};
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
  }
} // namespace ode::sdl
