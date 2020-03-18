//===--------------------------- map_loading.h ------------------*- C++ -*-===//
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
/// \file map_loading.h
/// \brief The declarations of the utility functions for loading the data of
/// the maps from the scripts.
/// \author Antti Kivi
/// \date 15 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_SYSTEMS_SCENES_WORLD_MAP_LOADING_H
#define ANTHEM_SYSTEMS_SCENES_WORLD_MAP_LOADING_H

#include <string>

#include "ode/__config"
#include "ode/lua/state_t.h"

namespace anthem::world
{
  ///
  /// \brief Loads the width of the map in tiles from the scripts.
  ///
  /// Remarks: The script containing the data of the map must be loaded into
  /// the Lua state before this function may be called.
  ///
  /// \param state the Lua state to be used.
  /// \param name the name of the map.
  ///
  /// \return The width of the map in tiles.
  ///
  int load_map_width(
      const ode::lua::state_ptr_t state,
      const std::string& name) ODE_CONTRACT_NOEXCEPT;
  

  ///
  /// \brief Loads the height of the map in tiles from the scripts.
  ///
  /// Remarks: The script containing the data of the map must be loaded into
  /// the Lua state before this function may be called.
  ///
  /// \param state the Lua state to be used.
  /// \param name the name of the map.
  ///
  /// \return The height of the map in tiles.
  ///
  int load_map_height(
      const ode::lua::state_ptr_t state,
      const std::string& name) ODE_CONTRACT_NOEXCEPT;

} // namespace anthem

#endif // !ANTHEM_SYSTEMS_SCENES_WORLD_MAP_LOADING_H
