//===-------------------------- thread_pool.cpp -----------------*- C++ -*-===//
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
/// \file thread_pool.cpp
/// \brief Definitions of thread-pooling functions.
/// \author Antti Kivi
/// \date 3 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/thread/thread_pool.h"

#include <functional>

namespace ode
{
  unsigned int number_of_threads() noexcept
  {
    return std::max(std::thread::hardware_concurrency(), 2u) - 1;
  }

  thread_pool::thread_pool(const unsigned int n) :
      count{static_cast<const int>(n)},
      queues{static_cast<std::size_t>(count)},
      index{0}
  {
    for (unsigned int i = 0; i < n; ++i)
    {
      threads.emplace_back([&, i]
      {
        run_thread(i);
      });
    }
  }

  thread_pool::~thread_pool()
  {
    for (auto& queue : queues)
    {
      queue.quit();
    }

    for (auto& thread : threads)
    {
      thread.join();
    }
  }

  void thread_pool::run_thread(const int i)
  {
    while (true)
    {
      std::function<void()> f;

      for (unsigned int n = 0; n != count; ++n)
      {
        if (queues[(i + n) % count].try_pop(f))
        {
          break;
        }
      }

      if (!f && !queues[i].pop(f))
      {
        break;
      }

      f();
    }
  }
} // namespace ode
