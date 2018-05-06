//===----------------------- notification_queue.cpp -------------*- C++ -*-===//
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
/// \file notification_queue.cpp
/// \brief The definition of the queue containing the tasks for thread pools.
/// \author Antti Kivi
/// \date 6 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/thread/notification_queue.h"

namespace ode
{
  notification_queue::notification_queue() : q{false}, c{}, m{}, cond{}
  {

  }

  bool notification_queue::try_pop(std::function<void()>& f)
  {
    lock_t l{m, std::try_to_lock};

    if (!l || c.empty())
    {
      return false;
    }

    f = std::move(c.front());
    c.pop_front();

    return true;
  }

  bool notification_queue::pop(std::function<void()>& f)
  {
    lock_t l{m};

    while (c.empty() && !q)
    {
      cond.wait(l);
    }

    if (c.empty())
    {
      return false;
    }

    f = std::move(c.front());
    c.pop_front();

    return true;
  }

  void notification_queue::quit()
  {
    {
      lock_t l{m};
      q = true;
    }

    cond.notify_all();
  }
} // namespace ode
