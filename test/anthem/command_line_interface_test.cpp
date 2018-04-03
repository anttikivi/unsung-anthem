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
/// \date 29 March 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/command_line_interface.h"

#include <gtest/gtest.h>

TEST(anthem_parse_arguments, parsed)
{
  const anthem::arguments a = {
      true,
      false,
      555_px,
      13_px,
      std::string{"window"}};
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
  const auto b = anthem::parse_arguments(4, argv_b);
  const auto c = anthem::parse_arguments(3, argv_c);
  const auto d = anthem::parse_arguments(7, argv_d);
  const auto e = anthem::parse_arguments(1, argv_e);
  const auto f = anthem::parse_arguments(3, argv_f);

  const std::string default_name = std::string{anthem::default_window_name};

  ASSERT_EQ(b, a);
  ASSERT_NE(c, a);
  ASSERT_EQ(b, d);
  ASSERT_EQ(d, a);
  ASSERT_EQ(e.window_width, anthem::default_window_width);
  ASSERT_EQ(e.window_height, anthem::default_window_height);
  ASSERT_EQ(e.window_height, anthem::default_window_height);
  ASSERT_EQ(e.window_name, default_name);
  ASSERT_EQ(f.window_width, anthem::default_window_width);
  ASSERT_NE(f.window_height, anthem::default_window_height);
  ASSERT_EQ(f.window_name, default_name);

  /*
  INFO("A: " << a);
  INFO("B: " << b);
  INFO("C: " << c);
  INFO("D: " << d);
  INFO("E: " << e);
  INFO("F: " << f);
  */
}

TEST(anthem_parse_arguments, help_argument)
{
  const anthem::arguments a = {true, true};
  ode::argv_array argv_b[] = {"exe", "--help"};
  const auto b = anthem::parse_arguments(2, argv_b);

  ASSERT_EQ(b.parsed, a.parsed);
  ASSERT_EQ(b.show_help, a.show_help);
  ASSERT_NE(b, a);
}

TEST(anthem_parse_arguments, parse_error_is_caught)
{
  const anthem::arguments a = {false};
  ode::argv_array argv_b[] = {"exe", "--xd"};
  const auto b = anthem::parse_arguments(2, argv_b);

  ASSERT_EQ(b, a);
}