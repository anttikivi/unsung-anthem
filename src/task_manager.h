//===------------------------ task_manager.h --------------------*- C++ -*-===//
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
/// \file task_manager.h
/// \brief Declaration of game framework task manager.
/// \author Antti Kivi
/// \date 28 November 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_TASK_MANAGER_H
#define ANTHEM_TASK_MANAGER_H

#include <vector>

#include "thread/thread_pool.h"

namespace anthem
{
  ///
  /// \brief The thread pool used by the task manager.
  ///
  /// \return Reference to the thread pool.
  ///
  thread_pool& task_thread_pool();

} // namespace anthem

#endif // !ANTHEM_TASK_MANAGER_H
