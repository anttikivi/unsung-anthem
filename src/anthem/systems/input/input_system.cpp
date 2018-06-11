//===-------------------------- input_system.cpp ----------------*- C++ -*-===//
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
/// \file input_system.cpp
/// \brief The definition of the type of the input system.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

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
