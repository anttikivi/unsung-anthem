/// The tests of the utility functions which allow to get data from the OpenGL
/// API.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/gl/data.h"

#include <cstring>

#include <gtest/gtest.h>

#include "ode/gl/gl_config.h"
#include "ode/logger.h"

TEST(ode_gl_data, vendor)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::get_vendor();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_VENDOR);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::get_vendor();

    ASSERT_EQ(r, s);
  }
}

TEST(ode_gl_data, renderer)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::get_renderer();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_RENDERER);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::get_renderer();

    ASSERT_EQ(r, s);
  }
}

TEST(ode_gl_data, version)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::get_version();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    auto original = glGetString(GL_VERSION);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
    auto s = std::string{reinterpret_cast<const char*>(original), len};

    auto r = ode::gl::get_version();

    ASSERT_EQ(r, s);
  }
}

TEST(ode_gl_data, shading_language_version)
{
  if constexpr (ode::disable_gl_calls)
  {
    auto r = ode::gl::get_shading_language_version();
    ASSERT_EQ(r, ode::gl::data::disabled_string_value);
  }
  else
  {
    const std::string gl_version = ode::gl::get_version();
    const int gl_major_version =
        std::stoi(gl_version.substr(0, gl_version.find(".")));

    if (ode::minimum_gl_major_version > gl_major_version)
    {
      auto r = ode::gl::get_shading_language_version();
      ASSERT_EQ(r, ode::gl::data::disabled_string_value);
    }
    else
    {
      auto original = glGetString(GL_SHADING_LANGUAGE_VERSION);
      std::size_t len = std::strlen(reinterpret_cast<const char*>(original));
      auto s = std::string{reinterpret_cast<const char*>(original), len};

      auto r = ode::gl::get_shading_language_version();

      ASSERT_EQ(r, s);
    }
  }
}
