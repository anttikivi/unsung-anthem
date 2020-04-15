/// The definition of the framework scene.
/// \file
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/framework/framework_scene.h"

#include "ode/config.h"
#include "ode/logger.h"
#include "ode/systems/scene_t.h"
#include "ode/systems/system_t.h"

namespace ode
{
  framework_scene::framework_scene(const scene_configuration_t& cfg)
      : config{cfg}, scenes{}
  {
    ODE_DEBUG("Reserving space for {} system scenes", system_space_reservation);
    scenes.reserve(system_space_reservation);
  }

  framework_scene::scene_reference framework_scene::extend(const system_t& sys)
  {
    // TODO
    return scenes.emplace_back(sys.make_scene({}));
  }
} // namespace ode
