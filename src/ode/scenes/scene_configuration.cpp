//===---------------------- scene_configuration.cpp -------------*- C++ -*-===//
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
/// \file scene_configuration.cpp
/// \brief The definition of the type of the scene configurations.
/// \author Antti Kivi
/// \date 5 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/scenes/scene_configuration.h"

#include <algorithm>

namespace ode
{
  scene_configuration::scene_configuration()
  {
    const auto a = system_types();
    systems = {a.cbegin(), a.cend()};
  }

  scene_configuration::scene_configuration(const std::vector<system_type>& d)
  {
    systems = {};
    for (auto a : system_types())
    {
      if (std::find(d.cbegin(), d.cend(), a) == d.cend())
      {
        systems.push_back(a);
      }
    }
  }
} // namespace ode
