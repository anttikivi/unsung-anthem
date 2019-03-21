//===---------------------------- system_t.cpp ------------------*- C++ -*-===//
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
/// \file system_t.cpp
/// \brief The definitions of the type templates of the system objects.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/systems/system_t.h"

namespace ode
{
  scene_t system_t::make_scene(const scene_configuration_t& cfg) const
  {
    return sys_ptr->make_scene(cfg);
  }
} // namespace ode
