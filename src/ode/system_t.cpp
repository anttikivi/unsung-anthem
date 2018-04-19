//===---------------------------- system_t.cpp ------------------*- C++ -*-===//
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
/// \file system_t.cpp
/// \brief Definitions of type templates of system objects of Obliging Ode.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/system_t.h"

#include "ode/scene_t.h"

namespace ode
{
  scene_t system_t::create_scene()
  {
    return sys_ptr->create_scene();
  }
} // namespace ode
