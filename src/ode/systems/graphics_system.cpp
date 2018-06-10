//===------------------------ graphics_system.cpp ---------------*- C++ -*-===//
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
/// \file graphics_system.cpp
/// \brief The definition of the type of the graphics system.
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/systems/graphics_system.h"

#include "ode/systems/graphics_scene.h"

namespace ode
{
  scene_t graphics_system::create_scene() const
  {
    return graphics_scene{};
  }
} // namespace ode
