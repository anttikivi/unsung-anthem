//===----------------------- thread_pool.cpp --------------------*- C++ -*-===//
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
/// \file thread_pool.cpp
/// \brief The definitions of the thread-pooling functions.
/// \author Antti Kivi
/// \date 27 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "thread_pool.h"

#include <algorithm>

namespace anthem
{
  unsigned int number_of_threads() noexcept
  {
    return std::max(std::thread::hardware_concurrency(), 2u) - 1;
  }

  thread_pool::thread_pool(const unsigned int n)
  : done{false}, thread_count{number_of_threads()}, queue{}, threads{}
  {
    for (unsigned int i = 0; i < thread_count; ++i)
    {
      threads.emplace_back([](thread_pool* pool)
      {
        while (!pool->done)
        {
        }
      }, this);
    }
  }
} // namespace anthem
