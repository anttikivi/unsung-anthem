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

namespace anthem
{
  unsigned int number_of_threads() noexcept
  {
    if (std::thread::hardware_concurrency() > 1)
    {
      return std::thread::hardware_concurrency() - 1;
    }
    else
    {
      return 1;
    }
  }
} // namespace anthem
