//===------------------------ universal_scene.cpp ---------------*- C++ -*-===//
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
/// \file universal_scene.cpp
/// \brief Definition of universal scene of Obliging Ode.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/universal_scene.h"

#include "ode/config.h"
#include "ode/logger.h"
#include "ode/scene_t.h"
#include "ode/system_t.h"

namespace ode
{
  universal_scene::universal_scene() : scenes{}
  {
    ODE_DEBUG(
        "Reserving space for {} system scenes",
        system_space_reservation);
    scenes.reserve(system_space_reservation);
  }

  universal_scene::scene_reference universal_scene::extend(const system_t sys)
  {
    scenes.push_back(sys.create_scene());
  }
} // namespace ode
