//===-------------------------- version_test.cpp ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file version_test.cpp
/// \brief The tests of the Simple DirectMedia Layer version utility functions.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#include "ode/sdl/sdl_version.h"

#include <gtest/gtest.h>

TEST(ode_sdl_version, compiled)
{
  auto v = ode::sdl::compiled_version();

  ASSERT_EQ(v.major, 2);
  ASSERT_EQ(v.minor, 0);
  ASSERT_EQ(v.patch, 12);

  SDL_version compiled;
  SDL_VERSION(&compiled);

  ASSERT_EQ(v.major, compiled.major);
  ASSERT_EQ(v.minor, compiled.minor);
  ASSERT_EQ(v.patch, compiled.patch);
}

TEST(ode_sdl_version, linked)
{
  auto v = ode::sdl::linked_version();

  ASSERT_EQ(v.major, 2);
  ASSERT_EQ(v.minor, 0);
  ASSERT_EQ(v.patch, 12);

  SDL_version linked;
  SDL_GetVersion(&linked);

  ASSERT_EQ(v.major, linked.major);
  ASSERT_EQ(v.minor, linked.minor);
  ASSERT_EQ(v.patch, linked.patch);
}
