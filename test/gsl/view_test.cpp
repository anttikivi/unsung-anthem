//===--- view_test.cpp ------------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file view_test.cpp
/// \brief Tests of the implementations of Guideline Support Library types
/// which allow distinction between owning and non-owning objects.
/// \author Antti Kivi
/// \date 30 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "gsl/view"

TEST_CASE("owner is equal to pointer", "[owner]") {

#if HAS_CXX17_TYPE_TRAITS

  constexpr bool a = std::is_same_v<gsl::owner<int*>, int*>;
  constexpr bool b = std::is_same_v<gsl::owner<int*>, int>;

#elif HAS_EXPERIMENTAL_TYPE_TRAITS

  constexpr bool a = std::experimental::is_same_v<gsl::owner<int*>, int*>;
  constexpr bool b = std::experimental::is_same_v<gsl::owner<int*>, int>;

#else

  constexpr bool a = std::is_same<gsl::owner<int*>, int*>::value;
  constexpr bool b = std::is_same<gsl::owner<int*>, int>::value;

#endif // !(HAS_CXX17_TYPE_TRAITS && HAS_EXPERIMENTAL_TYPE_TRAITS)

  REQUIRE(a);
  REQUIRE_FALSE(b);
}

TEST_CASE("type cast operator of not_null works", "[not_null]") {
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(s == decltype(s)(n));
  REQUIRE(*s == *decltype(s)(n));

  delete s;
}

TEST_CASE("member access operator of not_null works", "[not_null]") {
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(s->size() == n->size());

  delete s;
}

TEST_CASE("dereference operator of not_null works", "[not_null]") {
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(*s == *n);

  delete s;
}

TEST_CASE("get() of not_null works", "[not_null]") {
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  REQUIRE(s == n.get());
  REQUIRE(*s == *n.get());

  delete s;
}

TEST_CASE("== operator of not_null works", "[not_null]") {
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s};
  const gsl::not_null<std::string*> n2{s};

  REQUIRE(n1 == n2);

  delete s;
}

TEST_CASE("!= operator of not_null works", "[not_null]") {
  const auto s1 = new std::string("Hello, world!");
  const auto s2 = new std::string("!dlrow ,olleW");
  const gsl::not_null<std::string*> n1{s1};
  const gsl::not_null<std::string*> n2{s2};

  REQUIRE(n1 != n2);

  delete s1;
  delete s2;
}

TEST_CASE("hash function of not_null works", "[not_null]") {
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s};
  const gsl::not_null<std::string*> n2{s};

  INFO("The hash of the first not_null is " << std::hash<gsl::not_null<std::string*>>{}(n1));
  INFO("The hash of the second not_null is " << std::hash<gsl::not_null<std::string*>>{}(n2));

  REQUIRE(std::hash<gsl::not_null<std::string*>>{}(n1) == std::hash<gsl::not_null<std::string*>>{}(n2));

  delete s;
}
