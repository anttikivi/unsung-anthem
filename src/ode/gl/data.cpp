//===------------------------------ data.cpp --------------------*- C++ -*-===//
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
/// \file data.cpp
/// \brief Definitions of utility functions which allow to get data from the
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

#include "gsl/assert"

#include "ode/logger.h"

namespace ode::gl
{
  std::string get_string(const GLenum name) noexcept
  {
    Expects(GL_VENDOR == name
        || GL_RENDERER == name
        || GL_VERSION == name
        || GL_SHADING_LANGUAGE_VERSION == name);
    auto s = glGetString(name);
    ODE_TRACE("Got the unsigned byte array '{}'", s);
    std::size_t len = std::strlen(reinterpret_cast<const char*>(s));
    ODE_TRACE("The length of the string is {}", len);
    return std::string{reinterpret_cast<const char*>(s), len};
  }

  std::string vendor() noexcept
  {
    ODE_TRACE("Getting the OpenGL vendor (GL_VENDOR)");
    return get_string(GL_VENDOR);
  }

  std::string renderer() noexcept
  {
    ODE_TRACE("Getting the OpenGL renderer (GL_RENDERER)");
    return get_string(GL_RENDERER);
  }

  std::string version() noexcept
  {
    ODE_TRACE("Getting the OpenGL version (GL_VERSION)");
    return get_string(GL_VERSION);
  }

  std::string shading_language_version() noexcept
  {
    ODE_TRACE(
        "Getting the OpenGL shading language version "
        "(GL_SHADING_LANGUAGE_VERSION)");
    return get_string(GL_SHADING_LANGUAGE_VERSION);
  }

} // namespace ode::gl
