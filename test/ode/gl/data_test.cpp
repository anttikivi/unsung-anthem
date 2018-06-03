//===--------------------------- data_test.cpp ------------------*- C++ -*-===//
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
/// \file data_test.cpp
/// \brief The tests of the utility functions which allow to get data from the
/// OpenGL API.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/gl/data.h"

#include <cstring>

#include "ode/config.h"

#include <gtest/gtest.h>

TEST(ode_gl_data, vendor)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::vendor();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_VENDOR);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::vendor();

    ASSERT_EQ(r, s);
  }
}

TEST(ode_gl_data, renderer)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::renderer();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_RENDERER);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::renderer();

    ASSERT_EQ(r, s);
  }
}

TEST(ode_gl_data, version)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::version();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_VERSION);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::version();

    ASSERT_EQ(r, s);
  }
}

TEST(ode_gl_data, shading_language_version)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::shading_language_version();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_SHADING_LANGUAGE_VERSION);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::shading_language_version();

    ASSERT_EQ(r, s);
  }
}
