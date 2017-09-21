//===---------------------- arguments_test.cpp ------------------*- C++ -*-===//
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
/// \file arguments_test.cpp
/// \brief Tests of the definitions of the utilities related to parsing command
/// line arguments.
/// \author Antti Kivi
/// \date 11 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "catch.hpp"

#include "arguments.h"

TEST_CASE("the arguments are parsed", "[anthem::parse_arguments]")
{
  const auto log = anthem::create_logger("test_logger");
  const anthem::arguments a = {true, 555_px, 13_px};
  const char* argv_b[] = {"exe", "--window-height=13", "--window-width=555"};
  const char* argv_c[] = {"exe", "--window-height=423", "--window-width=22"};
  const auto b = anthem::parse_arguments(log, 3, argv_b);
  const auto c = anthem::parse_arguments(log, 3, argv_c);

  REQUIRE(b == a);
  REQUIRE_FALSE(b != a);
  REQUIRE_FALSE(c == a);
  REQUIRE(c != a);
}
