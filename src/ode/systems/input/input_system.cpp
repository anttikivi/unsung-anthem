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
/// \brief The definition of the type of the input system object.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/systems/input/input_system.h"

#include "ode/systems/input/input_scene.h"

namespace ode
{
  scene_t input_system::make_scene(const scene_configuration_t& cfg) const
  {
    return input_scene{};
  }
} // namespace ode
