/// The definition of the type of the input system object.
/// \file
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/systems/input/input_system.h"

#include "ode/systems/input/input_scene.h"

namespace ode
{
  scene_t input_system::make_scene(const scene_configuration_t& cfg) const
  {
    return input_scene{};
  }
} // namespace ode
