/// The declarations of the utility functions which are used to get data from
/// the OpenGL API.
/// \file
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_GL_DATA_H
#define ODE_GL_DATA_H

#include <string>

#include <glad/glad.h>

namespace ode::gl
{
  namespace data
  {
    ///
    /// The value returned by the data calls when OpenGL is disabled.
    ///
    constexpr auto disabled_string_value = "call_disabled";

  } // namespace data

  ///
  /// Gives an OpenGL data string.
  ///
  /// \param name a symbolic constant with which the value is got.
  ///
  /// \return An object of type \c std::string.
  ///
  std::string get_string(const GLenum name) noexcept;

  ///
  /// Gives the vendor of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the vendor.
  ///
  std::string vendor() noexcept;

  ///
  /// Gives the renderer of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the renderer.
  ///
  std::string renderer() noexcept;

  ///
  /// Gives the version of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the version.
  ///
  std::string version() noexcept;

  ///
  /// Gives the shading language version of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the shading
  /// language version.
  ///
  std::string shading_language_version() noexcept;

} // namespace ode::gl

#endif // !ODE_GL_DATA_H
