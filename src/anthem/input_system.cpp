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
/// \brief Definition of type of input system object of Unsung Anthem.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/input_system.h"

#include "ode/scene_t.h"

#include "anthem/input_scene.h"

namespace anthem
{
  ode::scene_t input_system::create_scene() const
  {
    return input_scene{};
  }
} // namespace anthem
