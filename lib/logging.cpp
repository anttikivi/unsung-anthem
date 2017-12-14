//===------------------------- logging.cpp ----------------------*- C++ -*-===//
//
//                            Unsung Anthem
//
// This source file is part of the Unsung Anthem open source project.
//
// Copyright (c) 2017 Venturesome Stone
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file logging.cpp
/// \brief Definitions of the logging-related utility functions.
/// \author Antti Kivi
/// \date 27 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#include "anthem/logging.h"

namespace anthem
{
  logger_t logger = nullptr;

  logger_t create_logger(
      const std::string& name,
      const std::string& pattern,
      const spdlog::level::level_enum level)
  {
    auto logger = spdlog::stdout_logger_mt(name);

    if (pattern != "NONE")
    {
      logger->set_pattern(pattern);
    }

    logger->set_level(level);

    return logger;
  }
} // namespace anthem
