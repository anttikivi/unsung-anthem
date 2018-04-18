//===----------------------------- event_t.h --------------------*- C++ -*-===//
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
/// \file event_t.h
/// \brief Declaration of type of objects which represent system events.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_EVENT_T_H
#define ODE_EVENT_T_H

#include <SDL2/SDL.h>

namespace ode
{
  ///
  /// \brief Type of objects which represent system events.
  ///
  using event_t = SDL_Event;

} // namespace ode

#endif // !ODE_EVENT_T_H
