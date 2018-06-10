//===------------------------------ argv_t.h --------------------*- C++ -*-===//
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
/// \file argv_t.h
/// \brief The declaration of the type of the argument array passed into the
/// main function.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_ARGV_T_H
#define ODE_ARGV_T_H

#include "ode/__config"

namespace ode
{
#if ODE_WINDOWS
  using argv_t = char*;
#else
  using argv_t = const char*;
#endif // !ODE_WINDOWS
} // namespace ode

#endif // !ODE_ARGV_T_H
