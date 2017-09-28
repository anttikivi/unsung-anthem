//===------------------------- schedule.cpp ---------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file schedule.cpp
/// \brief Definition of game update task scheduler.
/// \author Antti Kivi
/// \date 28 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "schedule.h"

namespace anthem
{
  thread_pool& scheduler_thread_pool()
  {
    static thread_pool p{};
    return p;
  }
} // namespace anthem
