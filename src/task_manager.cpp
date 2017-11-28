//===----------------------- task_manager.cpp -------------------*- C++ -*-===//
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
/// \file task_manager.cpp
/// \brief Definition of game framework task manager.
/// \author Antti Kivi
/// \date 28 November 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "task_manager.h"

namespace anthem
{
  thread_pool& task_thread_pool()
  {
    static thread_pool p{};
    return p;
  }
} // namespace anthem
