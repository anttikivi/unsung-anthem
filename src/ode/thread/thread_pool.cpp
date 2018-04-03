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
/// \brief Definitions of the thread-pooling functions.
/// \author Antti Kivi
/// \date 3 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/thread/thread_pool.h"

#include <algorithm>

namespace ode
{
  unsigned int number_of_threads() noexcept
  {
    return std::max(std::thread::hardware_concurrency(), 2u) - 1;
  }

  thread_pool::thread_pool(const unsigned int n) :
      quit{false},
      c{},
      cond{},
      m{},
      threads{}
  {
    for (unsigned int i = 0; i < n; ++i)
    {
      threads.emplace_back([this]
      {
        for(;;)
        {
          std::function<void()> t;

          {
            std::unique_lock<std::mutex> lock{this->m};

            this->cond.wait(lock, [this]
            {
              return this->quit || !this->c.empty();
            });

            if(this->quit && this->c.empty())
            {
              return;
            }

            t = std::move(this->c.front());
            this->c.pop();
          }

          t();
        }
      });
    }
  }

  thread_pool::~thread_pool()
  {
    {
      std::unique_lock<std::mutex> lock{m};
      quit = true;
    }

    cond.notify_all();

    for (auto& thread : threads)
    {
      thread.join();
    }
  }
} // namespace ode
