//===---------------------------- util_test.h -------------------*- C++ -*-===//
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
/// \file util_test.cpp
/// \brief Tests of the implementations of guideline support library utility
/// types.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include <catch.hpp>

#include "gsl/util"

TEST_CASE(
    "the Callable is invoked at the end of the scope",
    "[gsl::final_action]")
{
  int i = 0;

  auto f = [&]()
  {
    ++i;
  };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    gsl::final_action<decltype(f)> a{f};
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE(1 == i);
}

TEST_CASE(
    "the Callable is not invoked twice if final_action is moved",
    "[gsl::final_action]")
{
  int i = 0;

  auto f = [&]()
  {
    ++i;
  };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    gsl::final_action<decltype(f)> a{f};
    gsl::final_action<decltype(f)> b{std::move(a)};
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE(1 == i);
  REQUIRE_FALSE(2 == i);
}

TEST_CASE(
    "final_action invoking the Callable correctly is created",
    "[gsl::finally]")
{
  int i = 0;

  auto f = [&]()
  {
    ++i;
  };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    auto a = gsl::finally<decltype(f)>(f);
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE(1 == i);

  {
    auto b = gsl::finally<decltype(f)>(std::move(f));
  }

  REQUIRE_FALSE(0 == i);
  REQUIRE_FALSE(1 == i);
  REQUIRE(2 == i);
}

TEST_CASE("cast is done as expected", "[gsl::narrow_cast]")
{
  int i = 0;
  auto j = gsl::narrow_cast<unsigned int>(i);

#if ODE_CXX14

  constexpr bool a = std::is_same<decltype(j), unsigned int>::value;
  constexpr bool b = std::is_same<decltype(j), int>::value;

#else

  constexpr bool a = std::is_same_v<decltype(j), unsigned int>;
  constexpr bool b = std::is_same_v<decltype(j), int>;

#endif // !ODE_CXX14

  REQUIRE(a);
  REQUIRE_FALSE(b);
}

TEST_CASE(
    "exception is thrown when the cast changes the value",
    "[gsl::narrow]")
{
  int i = -1;

  REQUIRE_THROWS_AS(gsl::narrow<unsigned int>(i), gsl::narrowing_error);
}

TEST_CASE(
    "exception is not thrown when the cast does not change the value",
    "[gsl::narrow]")
{
  int i = 1;

  REQUIRE_NOTHROW(gsl::narrow<unsigned int>(i));
}

TEST_CASE("checked cast is done as expected", "[gsl::narrow]")
{
  int i = 0;
  auto j = gsl::narrow<unsigned int>(i);

#if ODE_CXX14

  constexpr bool a = std::is_same<decltype(j), unsigned int>::value;
  constexpr bool b = std::is_same<decltype(j), int>::value;

#else

  constexpr bool a = std::is_same_v<decltype(j), unsigned int>;
  constexpr bool b = std::is_same_v<decltype(j), int>;

#endif // !ODE_CXX14

  REQUIRE(a);
  REQUIRE_FALSE(b);
}

TEST_CASE("value does not change", "[gsl::narrow]")
{
  int i = 326;
  auto j = gsl::narrow<unsigned int>(i);

  unsigned int k = 326;

  REQUIRE(j == k);
}

TEST_CASE("narrowing_error is thrown", "[gsl::narrow]")
{
  int i = -326;
  REQUIRE_THROWS(gsl::narrow<unsigned int>(i));
  REQUIRE_THROWS_AS(gsl::narrow<unsigned int>(i), gsl::narrowing_error);
}
