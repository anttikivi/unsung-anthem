/// The tests of the guideline support library utility types.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "gsl/util"

#include <gtest/gtest.h>

TEST(gsl_final_action, invoked)
{
  int i = 0;

  auto f = [&]() { ++i; };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    gsl::final_action<decltype(f)> a{f};
  }

  ASSERT_NE(i, 0);
  ASSERT_EQ(i, 1);
}

TEST(gsl_final_action, invoked_twice)
{
  int i = 0;

  auto f = [&]() { ++i; };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    gsl::final_action<decltype(f)> a{f};
    gsl::final_action<decltype(f)> b{std::move(a)};
  }

  ASSERT_NE(i, 0);
  ASSERT_EQ(i, 1);
  ASSERT_NE(i, 2);
}

TEST(gsl_final_action, double_invocation)
{
  int i = 0;

  auto f = [&]() { ++i; };

  // Create a scope where the final_action is so it gets destructed and the
  // function is invoked.
  {
    auto a = gsl::finally<decltype(f)>(f);
  }

  ASSERT_NE(i, 0);
  ASSERT_EQ(i, 1);

  {
    auto b = gsl::finally<decltype(f)>(std::move(f));
  }

  ASSERT_NE(i, 0);
  ASSERT_NE(i, 1);
  ASSERT_EQ(i, 2);
}

TEST(gsl_narrow_cast, done)
{
  int i = 0;
  auto j = gsl::narrow_cast<unsigned int>(i);

  constexpr bool a = std::is_same_v<decltype(j), unsigned int>;
  constexpr bool b = std::is_same_v<decltype(j), int>;

  ASSERT_TRUE(a);
  ASSERT_FALSE(b);
}

TEST(gsl_narrow, throws)
{
  int i = -1;

  ASSERT_THROW(gsl::narrow<unsigned int>(i), gsl::narrowing_error);
}

TEST(gsl_narrow, no_throw)
{
  int i = 1;

  ASSERT_NO_THROW(gsl::narrow<unsigned int>(i));
}

TEST(gsl_narrow, casts)
{
  int i = 0;
  auto j = gsl::narrow<unsigned int>(i);

  constexpr bool a = std::is_same_v<decltype(j), unsigned int>;
  constexpr bool b = std::is_same_v<decltype(j), int>;

  ASSERT_TRUE(a);
  ASSERT_FALSE(b);
}

TEST(gsl_narrow, value_does_not_change)
{
  int i = 326;
  auto j = gsl::narrow<unsigned int>(i);

  unsigned int k = 326;

  ASSERT_EQ(j, k);
}

TEST(gsl_narrow, narrowing_error_is_thrown)
{
  int i = -326;
  ASSERT_ANY_THROW(gsl::narrow<unsigned int>(i));
  ASSERT_THROW(gsl::narrow<unsigned int>(i), gsl::narrowing_error);
}
