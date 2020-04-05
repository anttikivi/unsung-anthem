/// The declarations and definitions of logger-related constants.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_LOGGING_CONFIG_H
#define ANTHEM_LOGGING_CONFIG_H

#include <spdlog/spdlog.h>

namespace anthem
{
  ///
  /// The name of the program logger.
  ///
#ifdef ANTHEM_LOGGER_NAME
  constexpr auto logger_name = ANTHEM_LOGGER_NAME;
#else
  constexpr auto logger_name = "anthem";
#endif // !defined(ANTHEM_LOGGER_NAME)

  ///
  /// The logging pattern of the program logger.
  ///
  constexpr auto logger_pattern = "[%l] [%d %b %Y] [%H.%M:%S] %v";

  ///
  /// The name of the program logger.
  ///
  constexpr auto logger_level = spdlog::level::trace;

} // namespace anthem

#endif // !ANTHEM_LOGGING_CONFIG_H
