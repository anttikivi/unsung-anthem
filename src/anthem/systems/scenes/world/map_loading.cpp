//===-------------------------- map_loading.cpp -----------------*- C++ -*-===//
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
/// \file map_loading.cpp
/// \brief The definitions of the utility functions for loading the data of the
/// maps from the scripts.
/// \author Antti Kivi
/// \date 15 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

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
} // namespace anthem
