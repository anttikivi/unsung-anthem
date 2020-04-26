/// The tests of the utilities related to parsing command line arguments.
/// \file
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "anthem/command_line_interface.h"

#include <gtest/gtest.h>

TEST(anthem_parse_arguments, parsed)
{
  const anthem::arguments a = {555, 13, std::string{"window"}};
  char* argv_b[] = {
      "exe",
      "--window-height=13",
      "--window-width=555",
      "--window-name=window"};
  char* argv_c[] = {"exe", "--window-height=423", "--window-width=22"};
  char* argv_d[] = {
      "exe",
      "--window-height",
      "13",
      "--window-width",
      "555",
      "--window-name",
      "window"};
  char* argv_e[] = {"exe"};
  char* argv_f[] = {"exe", "--window-height", "13"};
  const auto [parsed_b, b] = anthem::parse_arguments(4, argv_b);
  const auto [parsed_c, c] = anthem::parse_arguments(3, argv_c);
  const auto [parsed_d, d] = anthem::parse_arguments(7, argv_d);
  const auto [parsed_e, e] = anthem::parse_arguments(1, argv_e);
  const auto [parsed_f, f] = anthem::parse_arguments(3, argv_f);

  const std::string default_name = std::string{anthem::default_window_name};

  ASSERT_TRUE(parsed_b);
  ASSERT_TRUE(parsed_c);
  ASSERT_TRUE(parsed_d);
  ASSERT_TRUE(parsed_e);
  ASSERT_TRUE(parsed_f);
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
}

TEST(anthem_parse_arguments, parse_error_is_caught)
{
  const anthem::arguments a = {};
  char* argv_b[] = {"exe", "--xd"};
  const auto [parsed_b, b] = anthem::parse_arguments(2, argv_b);

  ASSERT_FALSE(parsed_b);
  ASSERT_EQ(b, a);
}
