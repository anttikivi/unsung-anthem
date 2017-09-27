//===------------------------ thread_pool.h ---------------------*- C++ -*-===//
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
/// \file thread_pool.h
/// \brief The declarations of the thread-pooling functions.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_THREAD_THREAD_POOL_H
#define ANTHEM_THREAD_THREAD_POOL_H

#include <functional>
#include <future>
#include <thread>
#include <utility>

#include "anthem/logging.h"

#include "task_queue.h"

namespace anthem
{
  ///
  /// \brief Returns the number of threads to be created in the thread pool.
  ///
  /// \return The number of threads to be created in the thread pool.
  ///
  unsigned int number_of_threads() noexcept;

  ///
  /// \struct thread_pool
  /// \brief Type of objects which hold a queue of functions and execute them
  /// in parallel.
  ///
  struct thread_pool final
  {
    ///
    /// \brief The number of threads in the thread pool.
    ///
    const unsigned int thread_count = number_of_threads();

    ///
    /// \brief The queue which holds the tasks to be executed.
    ///
    task_queue<std::function<void()>> queue;

    template <class F, class... Args> auto queue_task(F&& f, Args&&... args)
    {
      auto bound = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

      using result_t = std::result_of_t<decltype(bound)()>;
      using packaged_t = std::packaged_task<result_t()>;
    }
  };
} // namespace anthem

#endif // !ANTHEM_THREAD_THREAD_POOL_H
