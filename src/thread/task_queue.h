//===------------------------ task_queue.h ----------------------*- C++ -*-===//
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
/// \file task_queue.h
/// \brief The declaration of the thread safe queue adaptor.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_THREAD_TASK_QUEUE_H
#define ANTHEM_THREAD_TASK_QUEUE_H

#include <condition_variable>
#include <mutex>
#include <queue>

#include "anthem/logging.h"

namespace anthem
{
  ///
  /// \struct task_container
  /// \brief Type of queue adaptors which allow the underlying container to
  /// hold objects in a thread safe manner.
  ///
  /// \tparam T the type of the objects held in the queue.
  /// \tparam Container the type of the underlying queue.
  /// \tparam Mutex the type of the mutex used to lock the queue.
  ///
  template <class T, class Container = std::queue<T>, class Mutex = std::mutex>
  struct task_queue final
  {
  public:

    ///
    /// \brief Returns the first element in the queue.
    ///
    /// \return The first value in the queue.
    ///
    T front()
    {
      std::unique_lock<Mutex> lock{m};
      cond.wait(lock, [this]()
      {
        return !c.empty(); // || !m_valid;
      });

      // if(!m_valid)
      // {
      //   return false;
      // }

      return c.front();
    }

    ///
    /// \brief Pushes the given element value to the end of the queue.
    ///
    /// \param value the value to be pushed.
    ///
    void push(const T& value)
    {
      std::lock_guard<Mutex> lock{m};
      c.push(value);
      cond.notify_one();
    }

    ///
    /// \brief Pushes the given element value to the end of the queue.
    ///
    /// \param value the value to be pushed.
    ///
    void push(T&& value)
    {
      std::lock_guard<Mutex> lock{m};
      c.push(std::move(value));
      cond.notify_one();
    }

    ///
    /// \brief Removes an element from the front of the queue.
    ///
    void pop()
    {
      std::lock_guard<Mutex> lock{m};
      c.pop();
    }

    ///
    /// \brief Returns the first element in the queue and removes it from the
    /// queue.
    ///
    /// \return The first value in the queue.
    ///
    T get_front()
    {
      std::unique_lock<Mutex> lock{m};
      cond.wait(lock, [this]()
      {
        return !c.empty(); // || !m_valid;
      });

      // if(!m_valid)
      // {
      //   return false;
      // }

      auto f = std::move(c.front());
      c.pop();
      return f;
    }

    ///
    /// \brief Returns a constant reference to the underlying queue for view.
    ///
    /// \return Constant reference to \c queue.
    ///
    const Container& view() const noexcept
    {
      return c;
    }

  private:

    ///
    /// \brief The underlying queue which holds the tasks.
    ///
    Container c;

    ///
    /// \brief The condition variable which is used to notify the threads
    /// whenever a new task is pushed to the queue.
    ///
    std::condition_variable cond;

    ///
    /// \brief The mutex used to lock the queue.
    ///
    Mutex m;
  };

  ///
  /// \brief Compares the two objects of type \c task_queue.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \tparam T the type of the objects held in the queue.
  /// \tparam Container the type of the underlying queue.
  /// \tparam Mutex the type of the mutex used to lock the queue.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  template <class T, class Container, class Mutex>
  constexpr const bool operator==(
      const task_queue<T, Container, Mutex>& lhs,
      const task_queue<T, Container, Mutex>& rhs) noexcept
  {
    return lhs.view() == rhs.view();
  }

  ///
  /// \brief Compares the two objects of type \c task_queue.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \tparam T the type of the objects held in the queue.
  /// \tparam Container the type of the underlying queue.
  /// \tparam Mutex the type of the mutex used to lock the queue.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  template <class T, class Container, class Mutex>
  constexpr const bool operator!=(
      const task_queue<T, Container, Mutex>& lhs,
      const task_queue<T, Container, Mutex>& rhs) noexcept
  {
    return !(lhs == rhs);
  }
} // namespace anthem

#endif // !ANTHEM_THREAD_TASK_QUEUE_H
