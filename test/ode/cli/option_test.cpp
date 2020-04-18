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
      "",
      ode::cli::boolean_meta_variable,
      ode::cli::option_type::boolean,
      true,
      false};

  ode::cli::option opt_1{"test-option", "t", "", true, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_boolean_invariant_without_short_name)
{
  ode::cli::option opt_base{
      "test-option",
      "",
      ode::cli::boolean_meta_variable,
      ode::cli::option_type::boolean,
      true,
      false};

  ode::cli::option opt_1{"test-option", "", true, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_integer_invariant)
{
  ode::cli::option opt_base{
      "test-option",
      "t",
      "",
      ode::cli::integer_meta_variable,
      ode::cli::option_type::integer,
      3,
      false};

  ode::cli::option opt_1{"test-option", "t", "", 3, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_integer_invariant_without_short_name)
{
  ode::cli::option opt_base{
      "test-option",
      "",
      ode::cli::integer_meta_variable,
      ode::cli::option_type::integer,
      7,
      false};

  ode::cli::option opt_1{"test-option", "", 7, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_float_invariant)
{
  ode::cli::option opt_base{
      "test-option",
      "t",
      "",
      ode::cli::float_meta_variable,
      ode::cli::option_type::floating_point,
      8.73,
      false};

  ode::cli::option opt_1{"test-option", "t", "", 8.73, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_float_invariant_without_short_name)
{
  ode::cli::option opt_base{
      "test-option",
      "",
      ode::cli::float_meta_variable,
      ode::cli::option_type::floating_point,
      13.664,
      false};

  ode::cli::option opt_1{"test-option", "", 13.664, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_string_invariant)
{
  using namespace std::literals::string_literals;
  ode::cli::option opt_base{
      "test-option",
      "t",
      "",
      ode::cli::string_meta_variable,
      ode::cli::option_type::string,
      "test value"s,
      false};

  ode::cli::option opt_1{"test-option", "t", "", "test value"s, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, valid_string_invariant_without_short_name)
{
  using namespace std::literals::string_literals;
  ode::cli::option opt_base{
      "test-option",
      "",
      ode::cli::string_meta_variable,
      ode::cli::option_type::string,
      "test value 2"s,
      false};

  ode::cli::option opt_1{"test-option", "", "test value 2"s, false};

  ASSERT_EQ(opt_base, opt_1);
}

TEST(ode_cli_option, parse_boolean_unix)
{
  ode::cli::option opt_0{"enable-something", "s", "", false, false};

  ode::argv_t argv_0[] = {
      "exe", "--enable-something", "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(
      3, argv_0, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_0 = std::get<bool>(*std::get<0>(p_0));

  ASSERT_TRUE(v_0);

  ode::cli::option opt_1{"enable-something", "s", "", false, false};

  ode::argv_t argv_1[] = {
      "exe", "-s", "--some-other-option=555", "--yet-another", "one"};

  auto p_1 = opt_1.parse_option(
      4, argv_1, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_1 = std::get<bool>(*std::get<0>(p_1));

  ASSERT_TRUE(v_1);

  ode::cli::option opt_2{"enable-something", "s", "", false, false};

  ode::argv_t argv_2[] = {
      "exe", "--enable-something", "true", "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(
      3, argv_2, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_2 = std::get<bool>(*std::get<0>(p_2));

  ASSERT_TRUE(v_2);

  ode::cli::option opt_3{"enable-something", "s", "", false, false};

  ode::argv_t argv_3[] = {
      "exe", "-s", "true", "--some-other-option=555", "--yet-another", "one"};

  auto p_3 = opt_3.parse_option(
      4, argv_3, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_3 = std::get<bool>(*std::get<0>(p_3));

  ASSERT_TRUE(v_3);

  ode::cli::option opt_4{"enable-something", "s", "", false, false};

  ode::argv_t argv_4[] = {
      "exe",
      "--enable-something=true",
      "--some-other-option=555",
      "--yet-another",
      "one"};

  auto p_4 = opt_4.parse_option(
      5, argv_4, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_4 = std::get<bool>(*std::get<0>(p_4));

  ASSERT_TRUE(v_4);

  ode::cli::option opt_5{"enable-something", "s", "", false, false};
  ode::cli::option opt_6{"some-option", "C", "", false, false};
  ode::cli::option opt_7{"this-is-option", "t", "", false, false};

  ode::argv_t argv_5[] = {
      "exe", "-Cst", "--some-other-option=555", "--yet-another", "one"};

  auto p_5 = opt_5.parse_option(
      5,
      argv_5,
      {std::cref(opt_5), std::cref(opt_6), std::cref(opt_7)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  bool v_5 = std::get<bool>(*std::get<0>(p_5));

  ASSERT_TRUE(v_5);

  ode::cli::option opt_8{"enable-something", "s", "", false, false};
  ode::cli::option opt_9{"some-option", "C", "", false, false};
  ode::cli::option opt_10{"this-is-option", "t", "", false, false};

  ode::argv_t argv_8[] = {
      "exe", "-Cts", "true", "--some-other-option=555", "--yet-another", "one"};

  auto p_8 = opt_8.parse_option(
      6,
      argv_8,
      {std::cref(opt_8), std::cref(opt_9), std::cref(opt_10)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  bool v_8 = std::get<bool>(*std::get<0>(p_8));

  ASSERT_TRUE(v_8);
}

TEST(ode_cli_option, parse_boolean_unix_reverse)
{
  ode::cli::option opt_0{"disable-something", "s", "", true, false};

  ode::argv_t argv_0[] = {
      "exe", "--disable-something", "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(
      3, argv_0, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_0 = std::get<bool>(*std::get<0>(p_0));

  ASSERT_FALSE(v_0);

  ode::cli::option opt_1{"disable-something", "s", "", true, false};

  ode::argv_t argv_1[] = {
      "exe", "-s", "--some-other-option=555", "--yet-another", "one"};

  auto p_1 = opt_1.parse_option(
      4, argv_1, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_1 = std::get<bool>(*std::get<0>(p_1));

  ASSERT_FALSE(v_1);

  ode::cli::option opt_2{"disable-something", "s", "", true, false};

  ode::argv_t argv_2[] = {
      "exe", "--disable-something", "false", "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(
      3, argv_2, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_2 = std::get<bool>(*std::get<0>(p_2));

  ASSERT_FALSE(v_2);

  ode::cli::option opt_3{"disable-something", "s", "", true, false};

  ode::argv_t argv_3[] = {
      "exe", "-s", "false", "--some-other-option=555", "--yet-another", "one"};

  auto p_3 = opt_3.parse_option(
      4, argv_3, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_3 = std::get<bool>(*std::get<0>(p_3));

  ASSERT_FALSE(v_3);

  ode::cli::option opt_4{"disable-something", "s", "", true, false};

  ode::argv_t argv_4[] = {
      "exe",
      "--disable-something=false",
      "--some-other-option=555",
      "--yet-another",
      "one"};

  auto p_4 = opt_4.parse_option(
      4, argv_4, {}, {}, "--", "-", "", "=", false, false, true);
  bool v_4 = std::get<bool>(*std::get<0>(p_4));

  ASSERT_FALSE(v_4);

  ode::cli::option opt_5{"disable-something", "s", "", true, false};
  ode::cli::option opt_6{"some-option", "C", "", false, false};
  ode::cli::option opt_7{"this-is-option", "t", "", false, false};

  ode::argv_t argv_5[] = {
      "exe", "-Cst", "--some-other-option=555", "--yet-another", "one"};

  auto p_5 = opt_5.parse_option(
      5,
      argv_5,
      {std::cref(opt_5), std::cref(opt_6), std::cref(opt_7)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  bool v_5 = std::get<bool>(*std::get<0>(p_5));

  ASSERT_FALSE(v_5);

  ode::cli::option opt_8{"disable-something", "s", "", true, false};
  ode::cli::option opt_9{"some-option", "C", "", false, false};
  ode::cli::option opt_10{"this-is-option", "t", "", false, false};

  ode::argv_t argv_8[] = {
      "exe",
      "-Cts",
      "false",
      "--some-other-option=555",
      "--yet-another",
      "one"};

  auto p_8 = opt_8.parse_option(
      6,
      argv_8,
      {std::cref(opt_8), std::cref(opt_9), std::cref(opt_10)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  bool v_8 = std::get<bool>(*std::get<0>(p_8));

  ASSERT_FALSE(v_8);
}

TEST(ode_cli_option, parse_integer_unix)
{
  ode::cli::option opt_0{"something", "s", "", 14, false};

  ode::argv_t argv_0[] = {"exe", "--something", "4", "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(
      4, argv_0, {}, {}, "--", "-", "", "=", false, false, true);
  int v_0 = std::get<int>(*std::get<0>(p_0));

  ASSERT_EQ(v_0, 4);

  ode::cli::option opt_1{"something", "s", "", 8, false};

  ode::argv_t argv_1[] = {
      "exe", "-s", "103", "--some-other-option=555", "--yet-another", "one"};

  auto p_1 = opt_1.parse_option(
      5, argv_1, {}, {}, "--", "-", "", "=", false, false, true);
  int v_1 = std::get<int>(*std::get<0>(p_1));

  ASSERT_EQ(v_1, 103);

  ode::cli::option opt_2{"something", "s", "", 22, false};

  ode::argv_t argv_2[] = {"exe", "--something=34", "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(
      3, argv_2, {}, {}, "--", "-", "", "=", false, false, true);
  int v_2 = std::get<int>(*std::get<0>(p_2));

  ASSERT_EQ(v_2, 34);

  ode::cli::option opt_3{"something", "s", "", 2, false};
  ode::cli::option opt_4{"some-option", "C", "", false, false};
  ode::cli::option opt_5{"this-is-option", "t", "", false, false};

  ode::argv_t argv_3[] = {
      "exe", "-Cts", "54", "--some-other-option=555", "--yet-another", "one"};

  auto p_3 = opt_3.parse_option(
      6,
      argv_3,
      {std::cref(opt_3), std::cref(opt_4), std::cref(opt_5)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  int v_3 = std::get<int>(*std::get<0>(p_3));

  ASSERT_EQ(v_3, 54);
}

TEST(ode_cli_option, parse_double_unix)
{
  ode::cli::option opt_0{"something", "s", "", 14.632, false};

  ode::argv_t argv_0[] = {
      "exe", "--something", "4.124", "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(
      4, argv_0, {}, {}, "--", "-", "", "=", false, false, true);
  double v_0 = std::get<double>(*std::get<0>(p_0));

  ASSERT_EQ(v_0, 4.124);

  ode::cli::option opt_1{"something", "s", "", 8.2, false};

  ode::argv_t argv_1[] = {
      "exe",
      "-s",
      "103.065",
      "--some-other-option=555",
      "--yet-another",
      "one"};

  auto p_1 = opt_1.parse_option(
      5, argv_1, {}, {}, "--", "-", "", "=", false, false, true);
  double v_1 = std::get<double>(*std::get<0>(p_1));

  ASSERT_EQ(v_1, 103.065);

  ode::cli::option opt_2{"something", "s", "", 22.3, false};

  ode::argv_t argv_2[] = {"exe", "--something=34.5", "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(
      3, argv_2, {}, {}, "--", "-", "", "=", false, false, true);
  double v_2 = std::get<double>(*std::get<0>(p_2));

  ASSERT_EQ(v_2, 34.5);

  ode::cli::option opt_3{"something", "s", "", 2.32, false};
  ode::cli::option opt_4{"some-option", "C", "", false, false};
  ode::cli::option opt_5{"this-is-option", "t", "", false, false};

  ode::argv_t argv_3[] = {
      "exe", "-Cts", "54.7", "--some-other-option=555", "--yet-another", "one"};

  auto p_3 = opt_3.parse_option(
      6,
      argv_3,
      {std::cref(opt_3), std::cref(opt_4), std::cref(opt_5)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  double v_3 = std::get<double>(*std::get<0>(p_3));

  ASSERT_EQ(v_3, 54.7);
}

TEST(ode_cli_option, parse_string_unix)
{
  ode::cli::option opt_0{"something-zero", "s", "", "strign", false};

  ode::argv_t argv_0[] = {
      "exe", "--something-zero", "a string", "--some-other-option=555"};

  auto p_0 = opt_0.parse_option(
      4, argv_0, {}, {}, "--", "-", "", "=", false, false, true);
  std::string v_0 = std::get<std::string>(*std::get<0>(p_0));

  ASSERT_EQ(v_0, "a string");

  ode::cli::option opt_1{"something-one", "s", "", "default", false};

  ode::argv_t argv_1[] = {
      "exe",
      "-s",
      "other value",
      "--some-other-option=555",
      "--yet-another",
      "one"};

  auto p_1 = opt_1.parse_option(
      5, argv_1, {}, {}, "--", "-", "", "=", false, false, true);
  std::string v_1 = std::get<std::string>(*std::get<0>(p_1));

  ASSERT_EQ(v_1, "other value");

  ode::cli::option opt_2{"something-two", "s", "", "default", false};

  ode::argv_t argv_2[] = {
      "exe", "--something-two=different string", "--some-other-option=555"};

  auto p_2 = opt_2.parse_option(
      3, argv_2, {}, {}, "--", "-", "", "=", false, false, true);
  std::string v_2 = std::get<std::string>(*std::get<0>(p_2));

  ASSERT_EQ(v_2, "different string");

  ode::cli::option opt_3{"something-three", "s", "", "default value", false};
  ode::cli::option opt_4{"some-option", "C", "", false, false};
  ode::cli::option opt_5{"this-is-option", "t", "", false, false};

  ode::argv_t argv_3[] = {
      "exe",
      "-Cts",
      "after combination",
      "--some-other-option=555",
      "--yet-another",
      "one"};

  auto p_3 = opt_3.parse_option(
      6,
      argv_3,
      {std::cref(opt_3), std::cref(opt_4), std::cref(opt_5)},
      {},
      "--",
      "-",
      "",
      "=",
      false,
      false,
      true);
  std::string v_3 = std::get<std::string>(*std::get<0>(p_3));

  ASSERT_EQ(v_3, "after combination");
}
