//===-------------------------- application.cpp -----------------*- C++ -*-===//
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
/// \file application.cpp
/// \brief The definition of the application type.
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/application.h"

#include <stdexcept>

#include "ode/systems/graphics_system.h"

namespace anthem
{
  ode::system_t application::make_system(const ode::system_type type)
  {
    if (ode::system_type::graphics == type)
    {
      return ode::graphics_system{};
    }

    // TODO
    throw std::runtime_error{""};
  }
} // namespace anthem
