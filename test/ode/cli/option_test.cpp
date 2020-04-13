/// The tests of the type of objects that contain information about one command
/// line option.
/// \file
/// \author Antti Kivi
/// \date 11 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/cli/option.h"

#include <gtest/gtest.h>

TEST(ode_cli_option, valid_boolean_invariant)
{
  ode::cli::option opt_base{
      "test-option",
      "t",
      ode::cli::option_type::boolean,
      true,
      false};

  ode::cli::option opt_1{"test-option", "t", true, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_boolean_invariant_without_short_name)
{
  ode::cli::option opt_base{
      "test-option",
      ode::cli::option_type::boolean,
      true,
      false};

  ode::cli::option opt_1{"test-option", true, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_integer_invariant)
{
  ode::cli::option opt_base{
      "test-option",
      "t",
      ode::cli::option_type::integer,
      3,
      false};

  ode::cli::option opt_1{"test-option", "t", 3, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_integer_invariant_without_short_name)
{
  ode::cli::option opt_base{
      "test-option",
      ode::cli::option_type::integer,
      7,
      false};

  ode::cli::option opt_1{"test-option", 7, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_float_invariant)
{
  ode::cli::option opt_base{
      "test-option",
      "t",
      ode::cli::option_type::floating_point,
      8.73,
      false};

  ode::cli::option opt_1{"test-option", "t", 8.73, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_float_invariant_without_short_name)
{
  ode::cli::option opt_base{
      "test-option",
      ode::cli::option_type::floating_point,
      13.664,
      false};

  ode::cli::option opt_1{"test-option", 13.664, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_string_invariant)
{
  using namespace std::literals::string_literals;
  ode::cli::option opt_base{
      "test-option",
      "t",
      ode::cli::option_type::string,
      "test value"s,
      false};

  ode::cli::option opt_1{"test-option", "t", "test value"s, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_string_invariant_without_short_name)
{
  using namespace std::literals::string_literals;
  ode::cli::option opt_base{
      "test-option",
      ode::cli::option_type::string,
      "test value 2"s,
      false};

  ode::cli::option opt_1{"test-option", "test value 2"s, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, parse_boolean_unix)
{
  ode::cli::option opt_0{"enable-something", "s", false, false};

  ode::argv_t argv_0[] = {
      "exe",
      "--enable-something",
      "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(3, argv_0, {}, "--", "-", "=", true);
  bool v_0 = std::get<bool>(*std::get<1>(p_0));

  ASSERT_TRUE(v_0);

  ode::cli::option opt_1{"enable-something", "s", false, false};

  ode::argv_t argv_1[] = {
      "exe",
      "-s",
      "--some-other-option=555",
      "--yet-another", "one"};

  auto p_1 = opt_1.parse_option(4, argv_1, {}, "--", "-", "=", true);
  bool v_1 = std::get<bool>(*std::get<1>(p_1));

  ASSERT_TRUE(v_1);

  ode::cli::option opt_2{"enable-something", "s", false, false};

  ode::argv_t argv_2[] = {
      "exe",
      "--enable-something", "true",
      "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(3, argv_2, {}, "--", "-", "=", true);
  bool v_2 = std::get<bool>(*std::get<1>(p_2));

  ASSERT_TRUE(v_2);

  ode::cli::option opt_3{"enable-something", "s", false, false};

  ode::argv_t argv_3[] = {
      "exe",
      "-s", "true",
      "--some-other-option=555",
      "--yet-another", "one"};

  auto p_3 = opt_3.parse_option(4, argv_3, {}, "--", "-", "=", true);
  bool v_3 = std::get<bool>(*std::get<1>(p_3));

  ASSERT_TRUE(v_3);

  ode::cli::option opt_4{"enable-something", "s", false, false};

  ode::argv_t argv_4[] = {
      "exe",
      "--enable-something=true",
      "--some-other-option=555",
      "--yet-another", "one"};

  auto p_4 = opt_4.parse_option(4, argv_4, {}, "--", "-", "=", true);
  bool v_4 = std::get<bool>(*std::get<1>(p_4));

  ASSERT_TRUE(v_4);
}

TEST(ode_cli_option, parse_boolean_unix_reverse)
{
  ode::cli::option opt_0{"disable-something", "s", true, false};

  ode::argv_t argv_0[] = {
      "exe",
      "--disable-something",
      "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(3, argv_0, {}, "--", "-", "=", true);
  bool v_0 = std::get<bool>(*std::get<1>(p_0));

  ASSERT_FALSE(v_0);

  ode::cli::option opt_1{"disable-something", "s", true, false};

  ode::argv_t argv_1[] = {
      "exe",
      "-s",
      "--some-other-option=555",
      "--yet-another", "one"};

  auto p_1 = opt_1.parse_option(4, argv_1, {}, "--", "-", "=", true);
  bool v_1 = std::get<bool>(*std::get<1>(p_1));

  ASSERT_FALSE(v_1);

  ode::cli::option opt_2{"disable-something", "s", true, false};

  ode::argv_t argv_2[] = {
      "exe",
      "--disable-something", "false",
      "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(3, argv_2, {}, "--", "-", "=", true);
  bool v_2 = std::get<bool>(*std::get<1>(p_2));

  ASSERT_FALSE(v_2);

  ode::cli::option opt_3{"disable-something", "s", true, false};

  ode::argv_t argv_3[] = {
      "exe",
      "-s", "false",
      "--some-other-option=555",
      "--yet-another", "one"};

  auto p_3 = opt_3.parse_option(4, argv_3, {}, "--", "-", "=", true);
  bool v_3 = std::get<bool>(*std::get<1>(p_3));

  ASSERT_FALSE(v_3);

  ode::cli::option opt_4{"disable-something", "s", true, false};

  ode::argv_t argv_4[] = {
      "exe",
      "--disable-something=false",
      "--some-other-option=555",
      "--yet-another", "one"};

  auto p_4 = opt_4.parse_option(4, argv_4, {}, "--", "-", "=", true);
  bool v_4 = std::get<bool>(*std::get<1>(p_4));

  ASSERT_FALSE(v_4);
}
