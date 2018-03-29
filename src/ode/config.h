//===------------------------------ config.h --------------------*- C++ -*-===//
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
/// \file config.h
/// \brief The declarations and the definitions of the Obliging Ode
/// miscellaneous constants.
/// \author Antti Kivi
/// \date 6 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_CONFIG_H
#define ODE_CONFIG_H

namespace ode
{
  ///
  /// \brief The name of the product.
  ///
#ifdef ODE_PRODUCT_NAME
  constexpr auto ode_name = ODE_PRODUCT_NAME;
#else
  constexpr auto ode_name = "Obliging Ode";
#endif // !defined(ODE_PRODUCT_NAME)

  ///
  /// \brief The root directory of the game scripts.
  ///
#ifdef ODE_SCRIPT_ROOT
  constexpr auto script_root = ODE_SCRIPT_ROOT;
#else
  constexpr auto script_root = "script/ode";
#endif // !defined(ODE_SCRIPT_ROOT)

  ///
  /// \brief The root directory of the test scripts.
  ///
#ifdef ODE_TEST_SCRIPT_ROOT
  constexpr auto test_script_root = ODE_TEST_SCRIPT_ROOT;
#else
  constexpr auto test_script_root = "script/test/ode";
#endif // !defined(ODE_TEST_SCRIPT_ROOT)

  ///
  /// \brief The major OpenGL version to be used.
  ///
#ifdef ODE_OPENGL_VERSION_MAJOR
  constexpr int opengl_version_major = ODE_OPENGL_VERSION_MAJOR;
#else
# error "ODE_OPENGL_VERSION_MAJOR is not set"
#endif // !defined(ODE_OPENGL_VERSION_MAJOR)

  ///
  /// \brief The minor OpenGL version to be used.
  ///
#ifdef ODE_OPENGL_VERSION_MINOR
  constexpr int opengl_version_minor = ODE_OPENGL_VERSION_MINOR;
#else
# error "ODE_OPENGL_VERSION_MINOR is not set"
#endif // !defined(ODE_OPENGL_VERSION_MINOR)

} // namespace ode

#endif // !ODE_CONFIG_H
