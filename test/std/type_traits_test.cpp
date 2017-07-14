//===--- type_traits_test.cpp -----------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file type_traits_test.cpp
/// \brief Tests of the implementations of C++ standard declarations related to
/// metaprogramming and type traits declarations.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "anthem/std/type_traits.h"

TEST_CASE("remove_cv_t works", "[remove_cv_t]") {

  typedef anthem::remove_cv_t<const int> a;
  typedef anthem::remove_cv_t<volatile int> b;
  typedef anthem::remove_cv_t<const volatile int> c;
  typedef anthem::remove_cv_t<volatile const int> d;

  const bool result_1 = std::is_same<int, a>::value;
  const bool result_2 = std::is_same<int, b>::value;
  const bool result_3 = std::is_same<int, c>::value;
  const bool result_4 = std::is_same<int, d>::value;

  REQUIRE(result_1);
  REQUIRE(result_2);
  REQUIRE(result_3);
  REQUIRE(result_4);

}
