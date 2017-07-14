//===--- utility_test.cpp ---------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file utility_test.cpp
/// \brief Tests of the implementations of C++ standard utility declarations.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include <type_traits>

#include "anthem/std/utility.h"

TEST_CASE("integer_sequence works", "[integer_sequence]") {

  typedef anthem::integer_sequence<int, 2, 5, 7> a;
  typedef anthem::integer_sequence<const int, 2, 5, 7> b;
  typedef anthem::integer_sequence<long, 2, 5, 7> c;

  SECTION("value_type gives correct type") {

    const bool result_a = std::is_same<a::value_type, int>::value;
    const bool result_b = std::is_same<b::value_type, const int>::value;
    const bool result_c = std::is_same<c::value_type, long>::value;

    REQUIRE(result_a);
    REQUIRE(result_b);
    REQUIRE(result_c);
  }

  SECTION("size gives correct length") {

    REQUIRE(3 == a::size());
    REQUIRE(3 == b::size());
    REQUIRE(3 == c::size());
  }
}

TEST_CASE("index_sequence works", "[index_sequence]") {

  typedef anthem::index_sequence<2, 5, 7> a;

  SECTION("value_type gives correct type") {

    const bool result_a = std::is_same<a::value_type, std::size_t>::value;

    REQUIRE(result_a);
  }

  SECTION("size gives correct length") {

    REQUIRE(3 == a::size());
  }
}

TEST_CASE("make_integer_sequence works", "[make_integer_sequence]") {

  typedef anthem::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6> a;
  typedef anthem::integer_sequence<const int, 0, 1, 2, 3, 4, 5, 6> b;
  typedef anthem::integer_sequence<long, 0, 1, 2, 3, 4, 5, 6> c;
  typedef anthem::integer_sequence<int, 0, 1, 2, 3, 4, 5> d;

  using ma = anthem::make_integer_sequence<int, 7>;
  using mb = anthem::make_integer_sequence<const int, 7>;
  using mc = anthem::make_integer_sequence<long, 7>;
  using md = anthem::make_integer_sequence<int, 6>;

  SECTION("value_type gives correct type") {

    const bool result_a = std::is_same<a::value_type, ma::value_type>::value;
    const bool result_b = std::is_same<b::value_type, mb::value_type>::value;
    const bool result_c = std::is_same<c::value_type, mc::value_type>::value;
    const bool result_d = std::is_same<d::value_type, md::value_type>::value;

    REQUIRE(result_a);
    REQUIRE(result_b);
    REQUIRE(result_c);
    REQUIRE(result_d);
  }

  SECTION("size gives correct length") {

    REQUIRE(a::size() == ma::size());
    REQUIRE(b::size() == mb::size());
    REQUIRE(c::size() == mc::size());
    REQUIRE(d::size() == md::size());
  }

  SECTION("make_integer_sequence produces correct type") {

    const bool result_a = std::is_same<a, ma>::value;
    const bool result_b = std::is_same<b, mb>::value;
    const bool result_c = std::is_same<c, mc>::value;
    const bool result_d = std::is_same<d, md>::value;

    REQUIRE(result_a);
    REQUIRE(result_b);
    REQUIRE(result_c);
    REQUIRE(result_d);
  }
}

TEST_CASE("make_index_sequence works", "[make_index_sequence]") {

  typedef anthem::index_sequence<0, 1, 2, 3, 4, 5, 6> a;
  typedef anthem::index_sequence<0, 1, 2, 3, 4, 5> b;

  using ma = anthem::make_index_sequence<7>;
  using mb = anthem::make_index_sequence<6>;

  SECTION("value_type gives correct type") {

    const bool result_a = std::is_same<a::value_type, ma::value_type>::value;
    const bool result_b = std::is_same<b::value_type, mb::value_type>::value;

    REQUIRE(result_a);
    REQUIRE(result_b);
  }

  SECTION("size gives correct length") {

    REQUIRE(a::size() == ma::size());
    REQUIRE(b::size() == mb::size());
  }

  SECTION("make_integer_sequence produces correct type") {

    const bool result_a = std::is_same<a, ma>::value;
    const bool result_b = std::is_same<b, mb>::value;

    REQUIRE(result_a);
    REQUIRE(result_b);
  }
}
