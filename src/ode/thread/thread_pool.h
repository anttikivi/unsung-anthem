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
/// \brief Declarations of the thread-pooling functions.
/// \author Antti Kivi
/// \date 3 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_THREAD_THREAD_POOL_H
#define ODE_THREAD_THREAD_POOL_H

#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <memory>
#include <queue>
#include <thread>
#include <utility>
#include <vector>

namespace ode
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

      {
        std::unique_lock<std::mutex> lock{m};

        if(quit)
        {
          // This isn't cool
          throw std::runtime_error("Enqueue on quitting thread_pool");
        }

        c.emplace([task]()
        {
          (*task)();
        });
      }

      cond.notify_one();
      return result;
    }

  private:

    ///
    /// \brief Whether or not the thread pool is quitting execution.
    ///
    std::atomic_bool quit;

    ///
    /// \brief Queue which holds tasks to be executed.
    ///
    std::queue<std::function<void()>> c;

    ///
    /// \brief The condition variable which is used to notify the threads
    /// whenever a new task is pushed to the queue.
    ///
    std::condition_variable cond;

    ///
    /// \brief The mutex used to lock the queue.
    ///
    std::mutex m;

    ///
    /// \brief Vector which holds the worker threads.
    ///
    std::vector<std::thread> threads;
  };
} // namespace ode

#endif // !ODE_THREAD_THREAD_POOL_H
