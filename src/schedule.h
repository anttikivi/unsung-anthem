//===-------------------------- schedule.h ----------------------*- C++ -*-===//
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
/// \file schedule.h
/// \brief Declaration of game update task scheduler.
/// \author Antti Kivi
/// \date 28 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_SCHEDULE_H
#define ANTHEM_SCHEDULE_H

#include "thread/thread_pool.h"

namespace anthem
{
  ///
  /// \brief The thread pool used by the scheduler.
  ///
  /// \return Reference to the thread pool.
  ///
  thread_pool& scheduler_thread_pool();

} // namespace anthem

#endif // !ANTHEM_SCHEDULE_H
