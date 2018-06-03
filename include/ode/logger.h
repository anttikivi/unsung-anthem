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
/// \brief The declarations of the main logging functions.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LOGGER_H
#define ODE_LOGGER_H

#include "ode/logging.h"

///
/// \def ODE_TRACE(...)
/// \brief The preprocessor macro used for trace-level logging.
///
#define ODE_TRACE(...) ::ode::logging::trace(__VA_ARGS__)

///
/// \def ODE_DEBUG(...)
/// \brief The preprocessor macro which is used for debug-level logging.
///
#define ODE_DEBUG(...) ::ode::logging::debug(__VA_ARGS__)

///
/// \def ODE_INFO(...)
/// \brief The preprocessor macro which is used for info-level logging.
///
#define ODE_INFO(...) ::ode::logging::info(__VA_ARGS__)

///
/// \def ODE_WARN(...)
/// \brief The preprocessor macro which is used for warning-level logging.
///
#define ODE_WARN(...) ::ode::logging::warn(__VA_ARGS__)

///
/// \def ODE_ERROR(...)
/// \brief The preprocessor macro which is used for error-level logging.
///
#define ODE_ERROR(...) ::ode::logging::error(__VA_ARGS__)

///
/// \def ODE_CRITICAL(...)
/// \brief The preprocessor macro which is used for critical-level logging.
///
#define ODE_CRITICAL(...) ::ode::logging::critical(__VA_ARGS__)

namespace ode
{
  ///
  /// \brief The main logger.
  ///
  inline logger_t logger = nullptr;
  
  // The logging methods which use the global logger.
  namespace logging
  {
    ///
    /// \brief Writes a trace-level log message into the logger.
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
    /// \brief Writes a trace-level log message into the logger.
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
    /// \brief Writes a debug-level log message into the logger.
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
    /// \brief Writes a debug-level log message into the logger.
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
    /// \brief Writes an info-level log message into the logger.
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
    /// \brief Writes an info-level log message into the logger.
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
    /// \brief Writes a warning-level log message into the logger.
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
    /// \brief Writes a warning-level log message into the logger.
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
    /// \brief Writes an error-level log message into the logger.
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
    /// \brief Writes an error-level log message into the logger.
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
    /// \brief Writes a critical-level log message into the logger.
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
    /// \brief Writes a critical-level log message into the logger.
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
