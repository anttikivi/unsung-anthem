/// The declarations and definitions of miscellaneous constants.
/// \file
/// \author Antti Kivi
/// \date 11 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_CONFIG_H
#define ODE_CONFIG_H

namespace ode
{
  ///
  /// The name of the product.
  ///
#ifdef ODE_PRODUCT_NAME
  constexpr auto ode_name = ODE_PRODUCT_NAME;
#else
  constexpr auto ode_name = "Obliging Ode";
#endif // !defined(ODE_PRODUCT_NAME)

  ///
  /// The root directory of the game scripts.
  ///
#ifdef ODE_SCRIPT_ROOT
  constexpr auto script_root = ODE_SCRIPT_ROOT;
#else
#  if _WIN32
  constexpr auto script_root = "lib\\ode";
#  else
  constexpr auto script_root = "lib/ode";
#  endif // !_WIN32
#endif // !defined(ODE_SCRIPT_ROOT)

  ///
  /// The root directory of the test scripts.
  ///
#ifdef ODE_TEST_SCRIPT_ROOT
  constexpr auto test_script_root = ODE_TEST_SCRIPT_ROOT;
#else
#  if _WIN32
  constexpr auto test_script_root = "lib\\ode";
#  else
  constexpr auto test_script_root = "lib/ode";
#  endif // !_WIN32
#endif // !defined(ODE_TEST_SCRIPT_ROOT)

  ///
  /// Whether or not the benchmarks are built.
  ///
#if ODE_TEST_BENCHMARKING
  constexpr bool test_benchmarking = true;
#else
  constexpr bool test_benchmarking = false;
#endif // !ODE_TEST_BENCHMARKING

  ///
  /// Whether or not the tests should use null sinks for loggers.
  ///
#if ODE_TEST_USE_NULL_SINK
  constexpr bool test_use_null_sink = true;
#else
  constexpr bool test_use_null_sink = false;
#endif // !ODE_TEST_USE_NULL_SINK

  ///
  /// The number of systems for which space is reserved in the system container
  /// initialization.
  ///
#ifdef ODE_SYSTEM_SPACE_RESERVATION
  constexpr int system_space_reservation = ODE_SYSTEM_SPACE_RESERVATION;
#else
  constexpr int system_space_reservation = 5;
#endif // !defined(ODE_SYSTEM_SPACE_RESERVATION)

} // namespace ode

#endif // !ODE_CONFIG_H
