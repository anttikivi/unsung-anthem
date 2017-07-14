//===--- array_test.cpp -----------------------------------------*- C++ -*-===//
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
/// \brief Tests of the implementations of array-related C++ standard
/// declarations.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "anthem/std/array.h"

TEST_CASE("to_array forms correct arrays", "[array]") {

  constexpr int a[]{2, 4, 5, 7, 11, 4321};

  constexpr std::array<int, 6> b{2, 4, 5, 7, 11, 4321};

  constexpr std::array<int, 6> c{2, 2, 5, 7, 11, 4321};

  constexpr auto result = anthem::to_array(a);

  REQUIRE(b == result);

  REQUIRE(c != result);
}
