//===---------------------------- system_t.cpp ------------------*- C++ -*-===//
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
/// \file system_t.cpp
/// \brief The definitions of the type templates of the system objects.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
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
