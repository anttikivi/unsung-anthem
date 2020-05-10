/// The definitions of the utility functions which allow to get data from the
/// OpenGL API.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/gl/data.h"

#include <cstring>

#include "gsl/assert"

#include "ode/__config"
#include "ode/gl/gl_config.h"
#include "ode/logger.h"

namespace ode::gl
{
  std::string get_string(const GLenum name)
  {
    Expects(
        GL_VENDOR == name || GL_RENDERER == name || GL_VERSION == name ||
        GL_SHADING_LANGUAGE_VERSION == name);

    if constexpr (disable_gl_calls)
    {
      return std::string{data::disabled_string_value};
    }
    else
    {
      auto s = glGetString(name);
      ODE_TRACE("Got the unsigned byte array '{}'", s);
      std::size_t len = std::strlen(reinterpret_cast<const char*>(s));
      ODE_TRACE("The length of the string is {}", len);
      return std::string{reinterpret_cast<const char*>(s), len};
    }
  }

  std::string get_vendor()
  {
    ODE_TRACE("Getting the OpenGL vendor (GL_VENDOR)");
    return get_string(GL_VENDOR);
  }

  std::string get_renderer()
  {
    ODE_TRACE("Getting the OpenGL renderer (GL_RENDERER)");
    return get_string(GL_RENDERER);
  }

  std::string get_version()
  {
    ODE_TRACE("Getting the OpenGL version (GL_VERSION)");
    return get_string(GL_VERSION);
  }

  std::string get_shading_language_version()
  {
    ODE_TRACE("Getting the OpenGL shading language version "
              "(GL_SHADING_LANGUAGE_VERSION)");

    if constexpr (disable_gl_calls)
    {
      return get_string(GL_SHADING_LANGUAGE_VERSION);
    }
    else
    {
      const std::string gl_version = get_version();
      const int gl_major_version =
          std::stoi(gl_version.substr(0, gl_version.find('.')));

      // The OpenGL shading language isn't supported in OpenGL versions below
      // 2.0
      if (minimum_gl_major_version > gl_major_version)
        ODE_UNLIKELY
        {
          ODE_TRACE(
              "The OpenGL shading language version isn't got as the OpenGL "
              "version {} doesn't support it",
              gl_version);
          return std::string{data::disabled_string_value};
        }
      else
      {
        return get_string(GL_SHADING_LANGUAGE_VERSION);
      }
    }
  }

} // namespace ode::gl
