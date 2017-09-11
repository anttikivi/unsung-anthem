//===------------------------ array_test.cpp --------------------*- C++ -*-===//
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
/// \file array_test.cpp
/// \brief Tests of the implementations of standard array utilities.
/// \author Antti Kivi
/// \date 11 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "anthem/array.h"

TEST_CASE("array is created as expected", "[anthem::std::to_array]") {
  const int a[] = {1, 3, 5, 8};
  const std::array<int, 4> b = {1, 3, 5, 8};
  const auto c = anthem::array::to_array(a);

  REQUIRE(b == c);
}
