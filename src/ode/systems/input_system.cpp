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
/// \brief The definition of the type of the input system object.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/input_system.h"

#include "ode/input_scene.h"
#include "ode/scene_t.h"

namespace ode
{
  scene_t input_system::create_scene() const
  {
    return input_scene{};
  }
} // namespace ode
