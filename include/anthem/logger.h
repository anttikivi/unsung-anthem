/// The declarations of the main logging functions.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_LOGGER_H
#define ANTHEM_LOGGER_H

#include "ode/logging.h"

///
/// The preprocessor macro which is used for trace-level logging.
/// \def ANTHEM_TRACE(...)
///
#define ANTHEM_TRACE(...) ::anthem::logging::trace(__VA_ARGS__)

///
/// The preprocessor macro which is used for debug-level logging.
/// \def ANTHEM_DEBUG(...)
///
#define ANTHEM_DEBUG(...) ::anthem::logging::debug(__VA_ARGS__)

///
/// The preprocessor macro which is used for info-level logging.
/// \def ANTHEM_INFO(...)
///
#define ANTHEM_INFO(...) ::anthem::logging::info(__VA_ARGS__)

///
/// The preprocessor macro which is used for warning-level logging.
/// \def ANTHEM_WARN(...)
///
#define ANTHEM_WARN(...) ::anthem::logging::warn(__VA_ARGS__)

///
/// The preprocessor macro which is used for error-level logging.
/// \def ANTHEM_ERROR(...)
///
#define ANTHEM_ERROR(...) ::anthem::logging::error(__VA_ARGS__)

///
/// The preprocessor macro which is used for critical-level logging.
/// \def ANTHEM_CRITICAL(...)
///
#define ANTHEM_CRITICAL(...) ::anthem::logging::critical(__VA_ARGS__)

namespace anthem
{
  ///
  /// The main logger.
  ///
  inline ode::logger_t logger = nullptr;

  // Logging methods which use the global logger.
  namespace logging
  {
    ///
    /// Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
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
    /// Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void trace(const T& msg)
    {
      ode::logging::trace(logger, msg);
    }

    ///
    /// Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
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
    /// Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void debug(const T& msg)
    {
      ode::logging::debug(logger, msg);
    }

    ///
    /// Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
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
    /// Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void info(const T& msg)
    {
      ode::logging::info(logger, msg);
    }

    ///
    /// Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
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
    /// Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void warn(const T& msg)
    {
      ode::logging::warn(logger, msg);
    }

    ///
    /// Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
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
    /// Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param msg the logger message.
    ///
    template <typename T> constexpr void error(const T& msg)
    {
      ode::logging::error(logger, msg);
    }

    ///
    /// Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
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
    /// Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
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
