//===--------------------------- thread_pool.h ------------------*- C++ -*-===//
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
/// \file thread_pool.h
/// \brief The declarations of the thread-pooling functions.
/// \author Antti Kivi
/// \date 5 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_THREAD_THREAD_POOL_H
#define ODE_THREAD_THREAD_POOL_H

#include <atomic>
#include <future>
#include <thread>
#include <vector>

#include "gsl/util"

#include "ode/thread/notification_queue.h"

namespace ode
{
  ///
  /// \brief Returns the number of threads to be created in a thread pool.
  ///
  /// \return Number of threads to be created in a thread pool.
  ///
  unsigned int number_of_threads() noexcept;

  ///
  /// \class thread_pool
  /// \brief Type of objects which hold a queue of functions and execute them
  /// in parallel.
  ///
  class thread_pool final
  {
  public:
    ///
    /// \brief Constructs an object of type \c thread_pool.
    ///
    /// \param n number of threads to be created.
    ///
    thread_pool(const unsigned int n = number_of_threads());

    ///
    /// \brief Constructs an object of type \c thread_pool by copying the given
    /// object of type \c thread_pool.
    ///
    /// \param a \c thread_pool from which the new one is constructed.
    ///
    thread_pool(const thread_pool& a) = delete;

    ///
    /// \brief Constructs an object of type \c thread_pool by moving the given
    /// object of type \c thread_pool.
    ///
    /// \param a \c thread_pool from which the new one is constructed.
    ///
    thread_pool(thread_pool&& a) = delete;

    ///
    /// \brief Destructs an object of type \c thread_pool.
    ///
    ~thread_pool();

    ///
    /// \brief Assigns the given object of type \c thread_pool to this one by
    /// copying.
    ///
    /// \param a \c thread_pool from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    thread_pool& operator=(const thread_pool& a) = delete;

    ///
    /// \brief Assigns the given object of type \c thread_pool to this one by
    /// moving.
    ///
    /// \param a \c thread_pool from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    thread_pool& operator=(thread_pool&& a) = delete;

    ///
    /// \brief Enqueues a task to be processed.
    ///
    /// \param f function which should be executed.
    /// \param args arguments which are passed to the function.
    ///
    /// \return An object of type \c std::future for getting the return value
    /// of the function.
    ///
    template <class F, class... Args> auto enqueue(F&& f, Args&&... args)
    {
      using return_t = std::result_of_t<F(Args...)>;

      auto task = std::make_shared<std::packaged_task<return_t()>>(std::bind(
          std::forward<F>(f),
          std::forward<Args>(args)...));

      std::future<return_t> result = task->get_future();

      auto i = index++;

      constexpr int loop_multiplier = 3;

      for (unsigned int n = 0; n < count * loop_multiplier; ++n)
      {
        if (queues[(i + n) % count].try_push([task](){(*task)();}))
        {
          return result;
        }
      }

      queues[i % count].push([task](){(*task)();});

      return result;
    }

  private:
    ///
    /// \brief The number of the threads in use.
    ///
    const int count;

    ///
    /// \brief A vector which holds the worker threads.
    ///
    std::vector<std::thread> threads;

    ///
    /// \brief A vector which holds the task queues for the worker threads.
    ///
    std::vector<notification_queue> queues;

    ///
    /// \brief The index of the thread to which something was last pushed.
    ///
    std::atomic<gsl::index> index;

    ///
    /// \brief Runs the execution of a worker thread.
    ///
    void run_thread(const int i);
  };
} // namespace ode

#endif // !ODE_THREAD_THREAD_POOL_H
