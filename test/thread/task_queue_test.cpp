//===--------------------- task_queue_test.cpp ------------------*- C++ -*-===//
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
/// \file task_queue_test.cpp
/// \brief Tests of the implementations of thread safe task queue.
/// \author Antti Kivi
/// \date 26 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include <string>

#include "thread/task_queue.h"

TEST_CASE("push, front, pop, and view", "[anthem::task_queue]")
{
  anthem::task_queue<std::string> q{};

  auto s = std::string{"Hello, World! Hopefully from a queue"};

  q.push(s);

  auto from_q_a1 = q.front();
  auto from_q_b1 = q.view().front();

  auto a = std::string{"Hello, World! Hopefully from a queue"};

  INFO("String in the queue is: " << from_q_a1);

  REQUIRE(a == from_q_a1);
  REQUIRE(a == q.front());
  REQUIRE(a == from_q_b1);
  REQUIRE(a == q.view().front());

  q.pop();

  q.push(std::move(s));

  auto from_q_a2 = q.front();
  auto from_q_b2 = q.view().front();

  auto b = std::string{"Hello, World! Hopefully from a queue"};

  INFO("String in the queue is: " << from_q_a2);

  REQUIRE(b == from_q_a2);
  REQUIRE(b == q.front());
  REQUIRE(a == from_q_b2);
  REQUIRE(a == q.view().front());

  q.pop();
}
