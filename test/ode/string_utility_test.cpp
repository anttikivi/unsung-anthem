/// The tests of the general string-related utilities.
/// \file
/// \author Antti Kivi
/// \date 12 April 2020
/// \copyright Copyright (c) 2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/string_utility.h"

#include <stdexcept>

#include <gtest/gtest.h>

TEST(ode_string_utility, is_integer)
{
  const std::string str_int{"1532"};
  const std::string str_int_prefix_0{"+14"};
  const std::string str_int_prefix_1{"-37"};
  const std::string str_not_int{"3 funny 4 string"};

  ASSERT_TRUE(ode::is_integer(str_int));
  ASSERT_TRUE(ode::is_integer(str_int_prefix_0));
  ASSERT_TRUE(ode::is_integer(str_int_prefix_1));
  ASSERT_FALSE(ode::is_integer(str_not_int));
}

TEST(ode_string_utility, trim)
{
  const std::string test_str_0{"a string"};
  const std::string test_str_1{"    a string"};
  const std::string test_str_2{"a string  "};
  const std::string test_str_3{"       a string      "};

  const auto trimmed_0 = ode::trim(test_str_0);
  const auto trimmed_1 = ode::trim(test_str_1);
  const auto trimmed_2 = ode::trim(test_str_2);
  const auto trimmed_3 = ode::trim(test_str_3);

  ASSERT_EQ(test_str_0, trimmed_0);
  ASSERT_EQ(test_str_0, trimmed_1);
  ASSERT_EQ(test_str_0, trimmed_2);
  ASSERT_EQ(test_str_0, trimmed_3);

  ASSERT_EQ(trimmed_0, trimmed_1);
  ASSERT_EQ(trimmed_1, trimmed_2);
  ASSERT_EQ(trimmed_2, trimmed_3);
}

TEST(ode_string_utility, string_to_boolean_parses)
{
  const std::string str_0{"true"};
  const std::string str_1{"false"};
  const std::string str_2{"10"};
  const std::string str_3{"0"};
  const std::string str_4{"-34"};

  const bool b_0 = ode::stob(str_0);
  const bool b_1 = ode::stob(str_1);
  const bool b_2 = ode::stob(str_2);
  const bool b_3 = ode::stob(str_3);
  const bool b_4 = ode::stob(str_4);

  ASSERT_TRUE(b_0);
  ASSERT_FALSE(b_1);
  ASSERT_TRUE(b_2);
  ASSERT_FALSE(b_3);
  ASSERT_TRUE(b_4);
}

TEST(ode_string_utility, string_to_boolean_throws)
{
  const std::string str_0{"not a bool"};

  ASSERT_THROW(ode::stob(str_0), std::invalid_argument);
}
