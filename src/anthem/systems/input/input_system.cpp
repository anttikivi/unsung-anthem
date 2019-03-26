//===-------------------------- input_system.cpp ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file input_system.cpp
/// \brief The definition of the type of the input system.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
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
