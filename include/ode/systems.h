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
/// \brief Declaration of system container of Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_H
#define ODE_SYSTEMS_H

#include <vector>

// Forward declaration
namespace ode
{
  class system_t;
} // namespace ode

namespace ode
{
  ///
  /// \brief Systems of Obliging Ode.
  ///
  extern std::vector<system_t> systems;

} // namespace ode

#endif // !ODE_SYSTEMS_H
