//===------------------------ graphics_system.cpp ---------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file graphics_system.cpp
/// \brief The definition of the type of the graphics system.
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/systems/graphics/graphics_system.h"

#include "ode/systems/graphics/graphics_scene.h"

namespace ode
{
  scene_t graphics_system::make_scene(const scene_configuration_t& cfg) const
  {
    return graphics_scene{};
  }
} // namespace ode
