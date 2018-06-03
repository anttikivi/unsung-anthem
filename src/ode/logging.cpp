//===---------------------------- logging.cpp -------------------*- C++ -*-===//
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
/// \file logging.cpp
/// \brief The definitions of the logging-related utility functions.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "ode/logging.h"

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
        return spdlog::stdout_logger_mt(name);
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
