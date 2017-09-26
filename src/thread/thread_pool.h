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
#include <utility>

#include "anthem/logging.h"

namespace anthem
{
  struct thread_pool final
  {

  }

  template <class F, class... Args> auto queue_task(F&& f, Args&&... args)
  {
    auto bound = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

    using result_t = std::result_of_t<decltype(bound)()>;
    using packaged_t = std::packaged_task<result_t()>;
  }
} // namespace anthem

#endif // !ANTHEM_THREAD_THREAD_POOL_H
