//===------------------------------- data.h ---------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file data.h
/// \brief The declarations of the utility functions which are used to get data
/// from the OpenGL API.
/// \author Antti Kivi
/// \date 10 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_GL_DATA_H
#define ODE_GL_DATA_H

#include <string>

#include <glad/glad.h>

namespace ode::gl
{
  namespace data
  {
    ///
    /// \brief The value returned by the data calls when OpenGL is disabled.
    ///
    constexpr auto disabled_string_value = "call_disabled";

  } // namespace data

  ///
  /// \brief Gives an OpenGL data string.
  ///
  /// \param name a symbolic constant with which the value is got.
  ///
  /// \return An object of type \c std::string.
  ///
  std::string get_string(const GLenum name) noexcept;

  ///
  /// \brief Gives the vendor of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the vendor.
  ///
  std::string vendor() noexcept;

  ///
  /// \brief Gives the renderer of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the renderer.
  ///
  std::string renderer() noexcept;

  ///
  /// \brief Gives the version of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the version.
  ///
  std::string version() noexcept;

  ///
  /// \brief Gives the shading language version of the currently used OpenGL.
  ///
  /// \return An object of type \c std::string which represents the shading
  /// language version.
  ///
  std::string shading_language_version() noexcept;

} // namespace ode::gl

#endif // !ODE_GL_DATA_H
