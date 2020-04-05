/// The definitions of the utility functions for loading the data of the maps
/// from the scripts.
/// \file
/// \author Antti Kivi
/// \date 15 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/systems/scenes/world/map_loading.h"

#include "ode/lua/virtual_machine.h"

namespace anthem::world
{
  int load_map_width(
      const ode::lua::state_ptr_t state,
      const std::string& name) ODE_CONTRACT_NOEXCEPT
  {
    const std::string var = name + ".width";
    return ode::lua::get<int>(state, var);
  }

  int load_map_height(
      const ode::lua::state_ptr_t state,
      const std::string& name) ODE_CONTRACT_NOEXCEPT
  {
    const std::string var = name + ".height";
    return ode::lua::get<int>(state, var);
  }
} // namespace anthem
