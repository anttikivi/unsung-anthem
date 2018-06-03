//===-------------------------- system_type.cpp -----------------*- C++ -*-===//
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
/// \file system_type.cpp
/// \brief The definitions of the system type utilities.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/systems/system_type.h"

namespace ode
{
  std::ostream& operator<<(std::ostream& os, const system_type& a)
  {
    return os << static_cast<ODE_SYSTEM_TYPE_ENUM_TYPE>(a);
  }
} // namespace ode
