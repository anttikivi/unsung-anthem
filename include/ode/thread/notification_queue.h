//===------------------------ notification_queue.h --------------*- C++ -*-===//
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
/// \file notification_queue.h
/// \brief The declaration of the queue containing the tasks for thread pools.
/// \author Antti Kivi
/// \date 5 May 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_THREAD_NOTIFICATION_QUEUE_H
#define ODE_THREAD_NOTIFICATION_QUEUE_H

#include <atomic>
#include <condition_variable>
#include <deque>
#include <functional>
#include <mutex>
#include <optional>
#include <utility>

namespace ode
{
  ///
  /// \class notification_queue
  /// \brief The type of objects which hold a queue of functions for executing
  /// them in parallel.
  ///
  class notification_queue final
  {
  public:

    ///
    /// \brief Constructs an object of type \c notification_queue.
    ///
    /// \param n number of threads to be created.
    ///
    notification_queue();

    ///
    /// \brief Constructs an object of type \c notification_queue by copying
    /// the given object of type \c notification_queue.
    ///
    /// \param a \c notification_queue from which the new one is constructed.
    ///
    notification_queue(const notification_queue& a) = delete;

    ///
    /// \brief Constructs an object of type \c notification_queue by moving the
    /// given object of type \c notification_queue.
    ///
    /// \param a \c notification_queue from which the new one is constructed.
    ///
    notification_queue(notification_queue&& a) = delete;

    ///
    /// \brief Destructs an object of type \c notification_queue.
    ///
    ~notification_queue() = default;

    ///
    /// \brief Assigns the given object of type \c notification_queue to this
    /// one by copying.
    ///
    /// \param a \c notification_queue from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    notification_queue& operator=(const notification_queue& a) = delete;

    ///
    /// \brief Assigns the given object of type \c notification_queue to this
    /// one by moving.
    ///
    /// \param a \c notification_queue from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    notification_queue& operator=(notification_queue&& a) = delete;

    ///
    /// \brief Attempts to pop the front of the queue.
    ///
    /// \param[out] f a reference to a function object to which the popped
    /// function is assigned.
    ///
    /// \return \c true if the pop was successful, otherwise \c false.
    ///
    bool try_pop(std::function<void()>& f);

    ///
    /// \brief Attempts to push to the back of the queue.
    ///
    /// \tparam F the type of the Callable which is pushed.
    ///
    /// \param f a Callable object which is pushed to queue.
    ///
    /// \return \c true if the push was successful, otherwise \c false.
    ///
    template <typename F> bool try_push(F&& f)
    {
      {
        lock_t l{m, std::try_to_lock};

        if (!l)
        {
          return false;
        }
        c.emplace_back(std::forward<F>(f));
      }

      cond.notify_one();
      return true;
    }

    ///
    /// \brief Pops the front of the queue.
    ///
    /// \param[out] f a reference to a function object to which the popped
    /// function is assigned.
    ///
    /// \return \c true if the pop was successful, otherwise \c false.
    ///
    bool pop(std::function<void()>& f);

    ///
    /// \brief Pushes to the back of the queue.
    ///
    /// \tparam F the type of the Callable which is pushed.
    ///
    /// \param f a Callable object which is pushed to queue.
    ///
    template <typename F> void push(F&& f)
    {
      {
        lock_t l{m, std::try_to_lock};
        c.emplace_back(std::forward<F>(f));
      }

      cond.notify_one();
    }

    ///
    /// \brief Marks the queue as quitting.
    ///
    void quit();

  private:
    ///
    /// \brief The type of the lock objects used in the queue.
    ///
    using lock_t = std::unique_lock<std::mutex>;

    ///
    /// \brief Whether or not the queue is quitting.
    ///
    std::atomic_bool q;

    ///
    /// \brief The double-ended queue which holds the tasks contained by this
    /// object.
    ///
    std::deque<std::function<void()>> c;

    ///
    /// \brief The mutex which is used to lock the queue.
    ///
    std::mutex m;

    ///
    /// \brief Condition variable which is used to notify the threads whenever
    /// a new task is pushed to the queue.
    ///
    std::condition_variable cond;
  };
} // namespace ode

#endif // !ODE_THREAD_NOTIFICATION_QUEUE_H
