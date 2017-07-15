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

  const auto result{anthem::parse_arguments(anthem::to_array(argv))};

  constexpr auto test = anthem::arguments{300, 15};

 // REQUIRE(result == test);
}

TEST_CASE("Argument array is successfully transformed into a string array",
          "[transform_to_strings]") {

  constexpr const char* argv[]{"executable", "--window-width", "300", "--window-height", "15"};
  const std::array<std::string, 5> test{"executable", "--window-width", "300", "--window-height", "15"};

  constexpr auto array = anthem::to_array(argv);

  const auto result = anthem::array::change_type<std::string>(array);

  REQUIRE(result == test);
}
