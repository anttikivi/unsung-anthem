/// The declarations and definitions of logger-related constants.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_LOGGING_CONFIG_H
#define ODE_LOGGING_CONFIG_H

#include <spdlog/spdlog.h>

namespace ode
{
  ///
  /// The name of the engine logger.
  ///
#ifdef ODE_LOGGER_NAME
  constexpr auto logger_name = ODE_LOGGER_NAME;
#else
  constexpr auto logger_name = "ode";
#endif // !defined(ODE_LOGGER_NAME)

  ///
  /// The logging pattern of the engine logger.
  ///
  constexpr auto logger_pattern = "[%l] [%d %b %Y] [%H.%M:%S] %v";

  ///
  /// The logging level of the engine logger.
  ///
  constexpr auto logger_level = spdlog::level::trace;

} // namespace ode

#endif // !ODE_LOGGING_CONFIG_H
