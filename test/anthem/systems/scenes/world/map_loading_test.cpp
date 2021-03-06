/// The tests of the utility functions for loading the data of the maps from
/// the scripts.
/// \file
/// \author Antti Kivi
/// \date 15 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/systems/scenes/world/map_loading.h"

#include <gtest/gtest.h>

#include "ode/filesystem/path.h"
#include "ode/lua/script.h"
#include "ode/lua/state.h"

#include "anthem/config.h"

TEST(anthem_systems_scenes_world_map_loading, width)
{
  auto state = ode::lua::make_state();
  const std::string name = "test";
  std::string s = std::string{anthem::script_root} +
      ode::filesystem::path::preferred_separator + "world" +
      ode::filesystem::path::preferred_separator + name +
      ode::filesystem::path::preferred_separator + "map.lua";
  ode::lua::load_script_file(state.get(), s);
  const auto width = anthem::world::load_map_width(state.get(), name);
  ASSERT_EQ(width, 100);
}

TEST(anthem_systems_scenes_world_map_loading, height)
{
  auto state = ode::lua::make_state();
  const std::string name = "test";
  std::string s = std::string{anthem::script_root} +
      ode::filesystem::path::preferred_separator + "world" +
      ode::filesystem::path::preferred_separator + name +
      ode::filesystem::path::preferred_separator + "map.lua";
  ode::lua::load_script_file(state.get(), s);
  const auto height = anthem::world::load_map_height(state.get(), name);
  ASSERT_EQ(height, 100);
}
