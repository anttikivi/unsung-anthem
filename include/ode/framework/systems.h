//===----------------------------- systems.h --------------------*- C++ -*-===//
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
/// \file systems.h
/// \brief The declaration of the system container.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_SYSTEMS_H
#define ODE_FRAMEWORK_SYSTEMS_H

#include <map>

#include "ode/systems/system_type.h"

// Forward declarations
namespace ode
{
  class system_t;
} // namespace ode

namespace ode
{
  ///
  /// \brief The systems.
  ///
  /// TODO Convert into a vector of pairs. That may be beneficial.
  ///
  extern std::map<system_type, system_t> systems;

} // namespace ode

#endif // !ODE_FRAMEWORK_SYSTEMS_H
