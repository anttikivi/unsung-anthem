//===----------------------- logging_config.h -------------------*- C++ -*-===//
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
/// \file logging_config.h
/// \brief The declarations and the definitions of the logger-related
/// constants.
/// \author Antti Kivi
/// \date 11 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_LOGGING_CONFIG_H
#define ANTHEM_LOGGING_CONFIG_H

#include <string>

#include <spdlog/spdlog.h>

namespace anthem
{
  ///
  /// \brief The name of the program logger.
  ///
#ifdef ANTHEM_LOGGER_NAME
  constexpr const auto logger_name = ANTHEM_LOGGER_NAME;
#else
  constexpr const auto logger_name = "anthem";
#endif // !defined(ANTHEM_LOGGER_NAME)

  ///
  /// \brief The logging pattern of the program logger.
  ///
  constexpr const auto logger_pattern = "[%l] [%d %b %Y] [%H.%M:%S] %v";

  ///
  /// \brief The name of the program logger.
  ///
  constexpr const auto logger_level = spdlog::level::trace;

} // namespace anthem

#endif // !ANTHEM_LOGGING_CONFIG_H
