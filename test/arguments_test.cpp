//===--- arguments_test.cpp -------------------------------------*- C++ -*-===//
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file arguments_test.cpp
/// \brief The declarations and definitions of the argument utility tests.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "arguments.h"

#include "anthem/std/array.h"

TEST_CASE("Arguments are parsed correctly", "[arguments]") {

  constexpr int argc = 5;
  constexpr const char* argv[] = {"executable", "--window-width", "300", "--window-height", "15"};

  constexpr auto result = anthem::parse_arguments(argc, anthem::to_array(argv));

  constexpr auto test = anthem::arguments{300, 15};

  REQUIRE(result == test);
}
