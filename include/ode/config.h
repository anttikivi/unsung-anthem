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
/// \brief The declarations and definitions of miscellaneous constants.
/// \author Antti Kivi
/// \date 11 April 2018
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
  /// \brief Whether or not the benchmarks are built.
  ///
#if ODE_TEST_BENCHMARKING
  constexpr bool test_benchmarking = true;
#else
  constexpr bool test_benchmarking = false;
#endif // !ODE_TEST_BENCHMARKING

  ///
  /// \brief Whether or not the OpenGL calls should be disabled.
  ///
#if ODE_DISABLE_GL_CALLS
  constexpr bool disable_gl_calls = true;
#else
  constexpr bool disable_gl_calls = false;
#endif // !ODE_DISABLE_GL_CALLS

  ///
  /// \brief Whether or not the tests should use null sinks for loggers.
  ///
#if ODE_TEST_USE_NULL_SINK
  constexpr bool test_use_null_sink = true;
#else
  constexpr bool test_use_null_sink = false;
#endif // !ODE_TEST_USE_NULL_SINK

  ///
  /// \brief The number of systems for which space is reserved in the system
  /// container initialization.
  ///
#ifdef ODE_SYSTEM_SPACE_RESERVATION
  constexpr int system_space_reservation = ODE_SYSTEM_SPACE_RESERVATION;
#else
  constexpr int system_space_reservation = 5;
#endif // !defined(ODE_SYSTEM_SPACE_RESERVATION)

} // namespace ode

#endif // !ODE_CONFIG_H
