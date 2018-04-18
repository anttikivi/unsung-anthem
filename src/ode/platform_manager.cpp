//===------------------------ platform_manager.cpp --------------*- C++ -*-===//
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
/// \file platform_manager.cpp
/// \brief Definition of manager which holds platform-related utilities of
/// Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/platform_manager.h"

#include "ode/logger.h"

namespace ode
{
  std::vector<event_t> poll_events()
  {
    std::vector<event_t> v{};
    event_t event;

    while (SDL_PollEvent(&event))
    {
      ODE_TRACE("System event: {}", event.type);
      v.push_back(event);
    }

    return v;
  }

} // namespace ode
