//===------------------------------ logger.h --------------------*- C++ -*-===//
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
/// \file logger.h
/// \brief Declarations of main logging functions of Unsung Anthem.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_LOGGER_H
#define ANTHEM_LOGGER_H

#include "ode/logging.h"

///
/// \def ANTHEM_TRACE(...)
/// \brief Preprocessor macro which is used for trace-level logging.
///
#define ANTHEM_TRACE(...) ::anthem::logging::trace(__VA_ARGS__)

///
/// \def ANTHEM_DEBUG(...)
/// \brief Preprocessor macro which is used for debug-level logging.
///
#define ANTHEM_DEBUG(...) ::anthem::logging::debug(__VA_ARGS__)

///
/// \def ANTHEM_INFO(...)
/// \brief Preprocessor macro which is used for info-level logging.
///
#define ANTHEM_INFO(...) ::anthem::logging::info(__VA_ARGS__)

///
/// \def ANTHEM_WARN(...)
/// \brief Preprocessor macro which is used for warning-level logging.
///
#define ANTHEM_WARN(...) ::anthem::logging::warn(__VA_ARGS__)

///
/// \def ANTHEM_ERROR(...)
/// \brief Preprocessor macro which is used for error-level logging.
///
#define ANTHEM_ERROR(...) ::anthem::logging::error(__VA_ARGS__)

///
/// \def ANTHEM_CRITICAL(...)
/// \brief Preprocessor macro which is used for critical-level logging.
///
#define ANTHEM_CRITICAL(...) ::anthem::logging::critical(__VA_ARGS__)

namespace anthem
{
  ///
  /// \brief The main logger of Unsung Anthem.
  ///
  inline ode::logger_t logger = nullptr;
  
  // Logging methods which use the global logger.
  namespace logging
  {
    ///
    /// \brief Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    constexpr void trace(const char* fmt, const Args&... args)
    {
      ode::logging::trace(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void trace(const T& msg)
    {
      ode::logging::trace(logger, msg);
    }
    
    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    constexpr void debug(const char* fmt, const Args&... args)
    {
      ode::logging::debug(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void debug(const T& msg)
    {
      ode::logging::debug(logger, msg);
    }
    
    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    constexpr void info(const char* fmt, const Args&... args)
    {
      ode::logging::info(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void info(const T& msg)
    {
      ode::logging::info(logger, msg);
    }
    
    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    constexpr void warn(const char* fmt, const Args&... args)
    {
      ode::logging::warn(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void warn(const T& msg)
    {
      ode::logging::warn(logger, msg);
    }
    
    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    constexpr void error(const char* fmt, const Args&... args)
    {
      ode::logging::error(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void error(const T& msg)
    {
      ode::logging::error(logger, msg);
    }
    
    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    constexpr void critical(const char* fmt, const Args&... args)
    {
      ode::logging::critical(logger, fmt, args...);
    }
    
    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void critical(const T& msg)
    {
      ode::logging::critical(logger, msg);
    }
    
  } // namespace logging
} // namespace anthem

#endif // !ANTHEM_LOGGER_H
