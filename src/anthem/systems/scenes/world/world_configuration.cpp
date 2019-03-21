//===---------------------- world_configuration.cpp -------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file world_configuration.cpp
/// \brief The definition of the type of the scene configurations for the basic
/// gameplay scenes.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/systems/scenes/world/world_configuration.h"

#include "ode/filesystem/path.h"
#include "ode/lua/script.h"

#include "anthem/config.h"
#include "anthem/systems/scenes/world/map_loading.h"

namespace anthem
{
  world_configuration::world_configuration(const std::string& n)
  : state{ode::lua::make_state()},
  name{n}
  {
    std::string s = std::string{script_root}
        + ode::filesystem::path::preferred_separator
        + "world"
        + ode::filesystem::path::preferred_separator
        + name
        + ode::filesystem::path::preferred_separator
        + "map.lua";
    ode::lua::load_script_file(state.get(), s);
    width = world::load_map_width(state.get(), name);
    height = world::load_map_height(state.get(), name);
  }
} // namespace anthem
