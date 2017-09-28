//===--------------------- thread_pool_test.cpp -----------------*- C++ -*-===//
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
/// \file thread_pool_test.cpp
/// \brief Tests of the implementations of the thread-pooling functions.
/// \author Antti Kivi
/// \date 27 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "thread/thread_pool.h"

TEST_CASE("number of threads is correct", "[anthem::number_of_threads]")
{
  using return_type = unsigned int;

  auto f = [](const int cores) -> return_type
  {
    if (cores > 1)
    {
      return cores - 1;
    }
    else
    {
      return 1;
    }
  };

  return_type concurrency = std::thread::hardware_concurrency();
  return_type expected = f(concurrency);
  return_type real = anthem::number_of_threads();

  REQUIRE(expected == real);

  concurrency = 1;
  expected = f(concurrency);
  real = 1;

  REQUIRE(expected == real);

  concurrency = 0;
  expected = f(concurrency);
  real = 1;

  REQUIRE(expected == real);

  concurrency = -1;
  expected = f(concurrency);
  real = 1;

  REQUIRE(expected == real);

  concurrency = 4;
  expected = f(concurrency);
  real = 3;

  REQUIRE(expected == real);
}

TEST_CASE("tasks are executed", "[anthem::thread_pool]")
{
  anthem::thread_pool pool{};

  auto add_3 = [](int i)
  {
    return 3 + i;
  };

  auto result_1 = pool.enqueue(add_3, 4);
  auto result_2 = pool.enqueue(add_3, 1);
  auto result_3 = pool.enqueue([](int i)
  {
    return 4 + i;
  }, 4);

  REQUIRE(result_1.get() == 7);
  REQUIRE(result_2.get() == 4);
  REQUIRE(result_3.get() == 8);
}
