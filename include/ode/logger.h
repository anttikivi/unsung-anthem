/// The declarations of the main logging functions.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_LOGGER_H
#define ODE_LOGGER_H

#include "ode/logging.h"

///
/// The preprocessor macro used for trace-level logging.
/// \def ODE_TRACE(...)
///
#define ODE_TRACE(...) ::ode::logging::trace(__VA_ARGS__)

///
/// The preprocessor macro which is used for debug-level logging.
/// \def ODE_DEBUG(...)
///
#define ODE_DEBUG(...) ::ode::logging::debug(__VA_ARGS__)

///
/// The preprocessor macro which is used for info-level logging.
/// \def ODE_INFO(...)
///
#define ODE_INFO(...) ::ode::logging::info(__VA_ARGS__)

///
/// The preprocessor macro which is used for warning-level logging.
/// \def ODE_WARN(...)
///
#define ODE_WARN(...) ::ode::logging::warn(__VA_ARGS__)

///
/// The preprocessor macro which is used for error-level logging.
/// \def ODE_ERROR(...)
///
#define ODE_ERROR(...) ::ode::logging::error(__VA_ARGS__)

///
/// The preprocessor macro which is used for critical-level logging.
/// \def ODE_CRITICAL(...)
///
#define ODE_CRITICAL(...) ::ode::logging::critical(__VA_ARGS__)

namespace ode
{
  ///
  /// The main logger.
  ///
  inline logger_t logger = nullptr;

  // The logging methods which use the global logger.
  namespace logging
  {
    ///
    /// Writes a trace-level log message into the logger.
    ///
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
    ///
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
    inline void trace(const char* fmt, const Args&... args)
    {
      trace(logger, fmt, args...);
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
    template <typename T> inline void trace(const T& msg)
    {
      trace(logger, msg);
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
    inline void debug(const char* fmt, const Args&... args)
    {
      debug(logger, fmt, args...);
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
    template <typename T> inline void debug(const T& msg)
    {
      debug(logger, msg);
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
    inline void info(const char* fmt, const Args&... args)
    {
      info(logger, fmt, args...);
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
    template <typename T> inline void info(const T& msg)
    {
      info(logger, msg);
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
    inline void warn(const char* fmt, const Args&... args)
    {
      warn(logger, fmt, args...);
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
    template <typename T> inline void warn(const T& msg)
    {
      warn(logger, msg);
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
    inline void error(const char* fmt, const Args&... args)
    {
      error(logger, fmt, args...);
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
    template <typename T> inline void error(const T& msg)
    {
      error(logger, msg);
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
    inline void critical(const char* fmt, const Args&... args)
    {
      critical(logger, fmt, args...);
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
    template <typename T>
    inline void critical(const T& msg)
    {
      critical(logger, msg);
    }

  } // namespace logging
} // namespace ode

#endif // !ODE_LOGGER_H
