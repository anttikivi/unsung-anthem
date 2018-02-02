//===---------------------------- view_test.h -------------------*- C++ -*-===//
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
/// \file view_test.cpp
/// \brief Tests of the implementations of guideline support library types
/// which allow distinction between owning and non-owning objects.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include <iostream>

#include "gsl/view"

TEST_CASE("is equal to pointer", "[gsl::owner]")
{
#if ODE_CXX14

  constexpr bool a = std::is_same<gsl::owner<int*>, int*>::value;
  constexpr bool b = std::is_same<gsl::owner<int*>, int>::value;

#else

  constexpr bool a = std::is_same_v<gsl::owner<int*>, int*>;
  constexpr bool b = std::is_same_v<gsl::owner<int*>, int>;

#endif // !ODE_CXX14

  REQUIRE(a);
  REQUIRE_FALSE(b);
}

TEST_CASE("type cast operator works", "[gsl::not_null]")
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(s == decltype(s)(n));
  REQUIRE(*s == *decltype(s)(n));

  delete s;
}

TEST_CASE("member access operator works", "[gsl::not_null]")
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(s->size() == n->size());

  delete s;
}

TEST_CASE("dereference operator works", "[gsl::not_null]")
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(*s == *n);

  delete s;
}

TEST_CASE("get() works", "[gsl::not_null]")
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(s == n.get());
  REQUIRE(*s == *n.get());

  delete s;
}

TEST_CASE("== operator works", "[gsl::not_null]")
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s};
  const gsl::not_null<std::string*> n2{s};

  REQUIRE(n1 == n2);

  delete s;
}

TEST_CASE("!= operator works", "[gsl::not_null]")
{
  const auto s1 = new std::string("Hello, world!");
  const auto s2 = new std::string("!dlrow ,olleW");
  const gsl::not_null<std::string*> n1{s1};
  const gsl::not_null<std::string*> n2{s2};

  REQUIRE(n1 != n2);

  delete s1;
  delete s2;
}

TEST_CASE("<< operator works", "[gsl::not_null]")
{
  const auto s1 = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s1};

  REQUIRE_NOTHROW(std::cout << "The address is " << n1 << std::endl);

  delete s1;
}

TEST_CASE("hash function works", "[gsl::not_null]")
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s};
  const gsl::not_null<std::string*> n2{s};

  INFO(
      "The hash of the first not_null is "
      << std::hash<gsl::not_null<std::string*>>{}(n1));
  INFO(
      "The hash of the second not_null is "
      << std::hash<gsl::not_null<std::string*>>{}(n2));

  REQUIRE(
      std::hash<gsl::not_null<std::string*>>{}(n1) ==
      std::hash<gsl::not_null<std::string*>>{}(n2));

  delete s;
}
