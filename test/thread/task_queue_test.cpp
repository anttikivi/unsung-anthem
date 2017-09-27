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

TEST_CASE("push, front, and pop", "[anthem::task_queue]")
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

TEST_CASE("get_front", "[anthem::task_queue]")
{
  anthem::task_queue<std::string> q1{};
  anthem::task_queue<std::string> q2{};

  auto s1 = std::string{"Hello, World! Hopefully from a queue"};
  auto s2 = std::string{"A second string"};

  q1.push(s1);
  q1.push(s2);

  q2.push(s2);

  auto s = q1.get_front();

  REQUIRE(s == s1);
  REQUIRE(s != q1.front());
  REQUIRE(s2 == q1.front());
  REQUIRE(q1 == q2);
}

TEST_CASE("underlying queue is correct", "[anthem::task_queue]")
{
  anthem::task_queue<std::string> q{};

  auto s1 = std::string{"Hello, World! Hopefully from a queue"};
  auto s2 = std::string{"A second string"};

  q.push(s1);
  q.push(s2);

  std::queue<std::string> standard{};

  standard.push(s1);
  standard.push(s2);

  REQUIRE(standard == q.view());
}

TEST_CASE("comparison works", "[anthem::task_queue]")
{
  anthem::task_queue<std::string> q1{};
  anthem::task_queue<std::string> q2{};
  anthem::task_queue<std::string> q3{};

  auto s1 = std::string{"Hello, World! Hopefully from a queue"};
  auto s2 = std::string{"A second string"};

  q1.push(s1);
  q1.push(s2);

  q2.push(s1);
  q2.push(s2);

  q3.push(s2);
  q3.push(s1);

  REQUIRE(q1 == q2);
  REQUIRE_FALSE(q1 != q2);

  REQUIRE_FALSE(q1 == q3);
  REQUIRE(q1 != q3);
}
