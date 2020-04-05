/// The definitions of the logging-related utility functions.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#include "ode/logging.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace ode
{
  namespace detail
  {
    logger_t make_logger(const std::string& name, const spdlog::sink_ptr sink)
    {
      // TODO Use the existing spdlog logger-creation functions for sinks which
      // have those.
      if (nullptr != sink)
      {
        return std::make_shared<spdlog::logger>(name, sink);
      }
      else
      {
        return spdlog::stdout_color_mt(name);
      }
    }
  } // namespace detail

  logger_t create_logger(
      const std::string& name,
      const std::string& pattern,
      const spdlog::level::level_enum level,
      const spdlog::sink_ptr sink)
  {

    auto logger = detail::make_logger(name, sink);

    if (pattern != "NONE")
    {
      logger->set_pattern(pattern);
    }

    logger->set_level(level);

    return logger;
  }
} // namespace ode
