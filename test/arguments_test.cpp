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
  const anthem::arguments a = {true, 555_px, 13_px, std::string{"window"}};
  const char* argv_b[] = {
      "exe",
      "--window-height=13",
      "--window-width=555",
      "--window-name=window"};
  const char* argv_c[] = {"exe", "--window-height=423", "--window-width=22"};
  const char* argv_d[] = {
      "exe",
      "--window-height", "13",
      "--window-width", "555",
      "--window-name", "window"};
  const char* argv_e[] = {"exe"};
  const char* argv_f[] = {"exe", "--window-height", "13"};
  const auto b = anthem::parse_arguments(4, argv_b);
  const auto c = anthem::parse_arguments(3, argv_c);
  const auto d = anthem::parse_arguments(7, argv_d);
  const auto e = anthem::parse_arguments(1, argv_e);
  const auto f = anthem::parse_arguments(3, argv_f);

  const std::string default_name = std::string{anthem::default_window_name};

  REQUIRE(b == a);
  REQUIRE_FALSE(b != a);
  REQUIRE_FALSE(c == a);
  REQUIRE(c != a);
  REQUIRE(b == d);
  REQUIRE_FALSE(b != d);
  REQUIRE(d == a);
  REQUIRE_FALSE(d != a);
  REQUIRE(e.window_width == anthem::default_window_width);
  REQUIRE(e.window_height == anthem::default_window_height);
  REQUIRE(e.window_height == anthem::default_window_height);
  REQUIRE(e.window_name == default_name);
  REQUIRE(f.window_width == anthem::default_window_width);
  REQUIRE_FALSE(f.window_height == anthem::default_window_height);
  REQUIRE(f.window_name == default_name);
}
