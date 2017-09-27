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

#include <atomic>
#include <functional>
#include <future>
#include <thread>
#include <utility>
#include <vector>

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
  public:
    ///
    /// \brief Constructs an object of type \c thread_pool.
    ///
    /// \param n the number of threads to be created.
    ///
    thread_pool(const unsigned int n = number_of_threads());

    template <class F, class... Args> auto queue_task(F&& f, Args&&... args)
    {
      auto bound = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

      using result_t = std::result_of_t<decltype(bound)()>;
      using packaged_t = std::packaged_task<result_t()>;
    }

  private:

    ///
    /// \brief Whether or not this pool should continue execution.
    ///
    std::atomic_bool done;

    ///
    /// \brief The number of threads in the thread pool.
    ///
    const unsigned int thread_count;

    ///
    /// \brief Queue which holds the tasks to be executed.
    ///
    task_queue<std::function<void()>> queue;

    ///
    /// \brief Vector which holds the worker threads.
    ///
    std::vector<std::thread> threads;
  };
} // namespace anthem

#endif // !ANTHEM_THREAD_THREAD_POOL_H
