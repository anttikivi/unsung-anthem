/// The definitions of the type templates of the system objects.
/// \file
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/systems/system_t.h"

namespace ode
{
  scene_t system_t::make_scene(const scene_configuration_t& cfg) const
  {
    return sys_ptr->make_scene(cfg);
  }
} // namespace ode
