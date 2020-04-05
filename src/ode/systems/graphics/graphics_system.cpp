/// The definition of the type of the graphics system.
/// \file
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/systems/graphics/graphics_system.h"

#include "ode/systems/graphics/graphics_scene.h"

namespace ode
{
  scene_t graphics_system::make_scene(const scene_configuration_t& cfg) const
  {
    return graphics_scene{};
  }
} // namespace ode
