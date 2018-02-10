//===------------------ command_line_interface_test.cpp ---------*- C++ -*-===//
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
/// \file command_line_interface_test.cpp
/// \brief Tests of the definitions of the utilities related to parsing command
/// line arguments.
/// \author Antti Kivi
/// \date 2 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/command_line_interface.h"

#include <catch.hpp>

TEST_CASE("the arguments are parsed", "[ode::parse_arguments]")
{
  const ode::arguments a = {true, false, 555_px, 13_px, std::string{"window"}};
  ode::argv_array argv_b[] = {
      "exe",
      "--window-height=13",
      "--window-width=555",
      "--window-name=window"};
  ode::argv_array argv_c[] = {
      "exe",
      "--window-height=423",
      "--window-width=22"};
  ode::argv_array argv_d[] = {
      "exe",
      "--window-height", "13",
      "--window-width", "555",
      "--window-name", "window"};
  ode::argv_array argv_e[] = {"exe"};
  ode::argv_array argv_f[] = {"exe", "--window-height", "13"};
  const auto b = ode::parse_arguments(4, argv_b);
  const auto c = ode::parse_arguments(3, argv_c);
  const auto d = ode::parse_arguments(7, argv_d);
  const auto e = ode::parse_arguments(1, argv_e);
  const auto f = ode::parse_arguments(3, argv_f);

  const std::string default_name = std::string{ode::default_window_name};

  REQUIRE(b == a);
  REQUIRE_FALSE(b != a);
  REQUIRE_FALSE(c == a);
  REQUIRE(c != a);
  REQUIRE(b == d);
  REQUIRE_FALSE(b != d);
  REQUIRE(d == a);
  REQUIRE_FALSE(d != a);
  REQUIRE(e.window_width == ode::default_window_width);
  REQUIRE(e.window_height == ode::default_window_height);
  REQUIRE(e.window_height == ode::default_window_height);
  REQUIRE(e.window_name == default_name);
  REQUIRE(f.window_width == ode::default_window_width);
  REQUIRE_FALSE(f.window_height == ode::default_window_height);
  REQUIRE(f.window_name == default_name);

  INFO("A: " << a);
  INFO("B: " << b);
  INFO("C: " << c);
  INFO("D: " << d);
  INFO("E: " << e);
  INFO("F: " << f);
}

TEST_CASE("help argument is set", "[ode::parse_arguments]")
{
  const ode::arguments a = {true, true};
  ode::argv_array argv_b[] = {"exe", "--help"};
  const auto b = ode::parse_arguments(2, argv_b);

  REQUIRE(b.parsed == a.parsed);
  REQUIRE(b.show_help == a.show_help);
  REQUIRE(b != a);
}

TEST_CASE("parse error is caught", "[ode::parse_arguments]")
{
  const ode::arguments a = {false};
  ode::argv_array argv_b[] = {"exe", "--xd"};
  const auto b = ode::parse_arguments(2, argv_b);

  REQUIRE(b == a);
  REQUIRE_FALSE(b != a);
}
