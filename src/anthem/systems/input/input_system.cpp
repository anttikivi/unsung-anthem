/// The definition of the type of the input system.
/// \file
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/systems/input/input_system.h"

#include "anthem/systems/input/input_scene.h"

namespace anthem
{
  ode::scene_t input_system::make_scene(
      const ode::scene_configuration_t& cfg) const
  {
    return ode::scene_t{input_scene{}};
  }
} // namespace anthem
