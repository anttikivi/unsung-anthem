//===-------------------------- logging_config.h ----------------*- C++ -*-===//
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
/// \file logging_config.h
/// \brief The declarations and definitions of logger-related constants.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LOGGING_CONFIG_H
#define ODE_LOGGING_CONFIG_H

#include <spdlog/spdlog.h>

namespace ode
{
  ///
  /// \brief The name of the engine logger.
  ///
#ifdef ODE_LOGGER_NAME
  constexpr auto logger_name = ODE_LOGGER_NAME;
#else
  constexpr auto logger_name = "ode";
#endif // !defined(ODE_LOGGER_NAME)

  ///
  /// \brief The logging pattern of the engine logger.
  ///
  constexpr auto logger_pattern = "[%l] [%d %b %Y] [%H.%M:%S] %v";

  ///
  /// \brief The name of the engine logger.
  ///
  constexpr auto logger_level = spdlog::level::trace;

} // namespace ode

#endif // !ODE_LOGGING_CONFIG_H
