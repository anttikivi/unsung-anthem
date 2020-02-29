//===---------------------------- gl_config.h -------------------*- C++ -*-===//
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
/// \file gl_config.h
/// \brief The declarations and definitions of the OpenGL-related constants.
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_GL_GL_CONFIG_H
#define ODE_GL_GL_CONFIG_H

namespace ode
{
  ///
  /// \brief The major OpenGL version number to be used.
  ///
#ifdef ODE_OPENGL_VERSION_MAJOR
  constexpr int opengl_version_major = ODE_OPENGL_VERSION_MAJOR;
#else
# error "ODE_OPENGL_VERSION_MAJOR is not set"
#endif // !defined(ODE_OPENGL_VERSION_MAJOR)

  ///
  /// \brief The minor OpenGL version number to be used.
  ///
#ifdef ODE_OPENGL_VERSION_MINOR
  constexpr int opengl_version_minor = ODE_OPENGL_VERSION_MINOR;
#else
# error "ODE_OPENGL_VERSION_MINOR is not set"
#endif // !defined(ODE_OPENGL_VERSION_MINOR)

  ///
  /// \brief The default swap interval setting to be used with OpenGL.
  ///
#ifdef ODE_OPENGL_SWAP_INTERVAL
  constexpr int opengl_swap_interval = ODE_OPENGL_SWAP_INTERVAL;
#else
  constexpr int opengl_swap_interval = 1;
#endif // !defined(ODE_OPENGL_SWAP_INTERVAL)

  ///
  /// \brief Whether or not the OpenGL calls should be disabled.
  ///
#if ODE_DISABLE_GL_CALLS
  constexpr bool disable_gl_calls = true;
#else
  constexpr bool disable_gl_calls = false;
#endif // !ODE_DISABLE_GL_CALLS

  ///
  /// \brief The minimum major version number of OpenGL that is required to use
  /// all features of the application.
  ///
  constexpr int minimum_gl_major_version = 2;

} // namespace ode

#endif // !ODE_GL_GL_CONFIG_H
