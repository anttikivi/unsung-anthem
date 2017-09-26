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
/// \brief The declaration of the thread safe task queue.
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
  /// \struct task_queue
  /// \brief Type of objects which hold objects in a thread safe manner.
  ///
  /// \tparam T the type of the objects held in the queue.
  ///
  template <class T> struct task_queue final
  {
  public:

    ///
    /// \brief Returns the first element in the queue.
    ///
    /// \return The first value in the queue.
    ///
    T front()
    {
      std::unique_lock<std::mutex> lock{mutex};
      cond.wait(lock, [this]()
      {
        return !queue.empty(); // || !m_valid;
      });

      // if(!m_valid)
      // {
      //   return false;
      // }

      return queue.front();
    }

    ///
    /// \brief Pushes the given element value to the end of the queue.
    ///
    /// \param value the value to be pushed.
    ///
    void push(const T& value)
    {
      std::lock_guard<std::mutex> lock{mutex};
      queue.push(value);
      cond.notify_one();
    }

    ///
    /// \brief Pushes the given element value to the end of the queue.
    ///
    /// \param value the value to be pushed.
    ///
    void push(T&& value)
    {
      std::lock_guard<std::mutex> lock{mutex};
      queue.push(std::move(value));
      cond.notify_one();
    }

    ///
    /// \brief Removes an element from the front of the queue.
    ///
    void pop()
    {
      std::lock_guard<std::mutex> lock{mutex};
      queue.pop();
    }

    ///
    /// \brief Returns a constant reference to the underlying queue for view.
    ///
    /// \return Constant reference to \c queue.
    ///
    const std::queue<T>& view() const noexcept
    {
      return queue;
    }

  private:

    ///
    /// \brief The underlying queue which holds the tasks.
    ///
    std::queue<T> queue;

    ///
    /// \brief The condition variable which is used to notify the threads
    /// whenever a new task is pushed to the queue.
    ///
    std::condition_variable cond;

    ///
    /// \brief The mutex used to lock the queue.
    ///
    std::mutex mutex;
  };
} // namespace anthem

#endif // !ANTHEM_THREAD_TASK_QUEUE_H
