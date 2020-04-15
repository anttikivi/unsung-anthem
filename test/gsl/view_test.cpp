/// The tests of the guideline support library types which are used as viewers
/// for various objects and which do distinction between owning and non-owning
/// types.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "gsl/view"

#include <iostream>

#include <gtest/gtest.h>

TEST(gsl_owner, is_equal_to_pointer)
{
  constexpr bool a = std::is_same_v<gsl::owner<int*>, int*>;
  constexpr bool b = std::is_same_v<gsl::owner<int*>, int>;

  ASSERT_TRUE(a);
  ASSERT_FALSE(b);
}

TEST(gsl_not_null, cast_operator)
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  ASSERT_EQ(s, decltype(s)(n));
  ASSERT_EQ(*s, *decltype(s)(n));

  delete s;
}

TEST(gsl_not_null, member_access_operator)
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  ASSERT_EQ(s->size(), n->size());

  delete s;
}

TEST(gsl_not_null, dereference_operator)
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  ASSERT_EQ(*s, *n);

  delete s;
}

TEST(gsl_not_null, get)
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n{s};

  ASSERT_EQ(s, n.get());
  ASSERT_EQ(*s, *n.get());

  delete s;
}

TEST(gsl_not_null, equal_comparison_operator)
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s};
  const gsl::not_null<std::string*> n2{s};

  ASSERT_TRUE(n1 == n2);

  delete s;
}

TEST(gsl_not_null, not_equal_comparison_operator)
{
  const auto s1 = new std::string("Hello, world!");
  const auto s2 = new std::string("!dlrow ,olleW");
  const gsl::not_null<std::string*> n1{s1};
  const gsl::not_null<std::string*> n2{s2};

  ASSERT_TRUE(n1 != n2);

  delete s1;
  delete s2;
}

TEST(gsl_not_null, bitwise_left_shift_operator)
{
  const auto s1 = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s1};

  ASSERT_NO_THROW(std::cout << "The address is " << n1 << std::endl);

  delete s1;
}

TEST(gsl_not_null, hash_function)
{
  const auto s = new std::string("Hello, world!");
  const gsl::not_null<std::string*> n1{s};
  const gsl::not_null<std::string*> n2{s};

  ASSERT_EQ(
      std::hash<gsl::not_null<std::string*>>{}(n1),
      std::hash<gsl::not_null<std::string*>>{}(n2));

  delete s;
}
