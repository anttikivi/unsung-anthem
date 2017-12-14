//===-------------------------- logging.h -----------------------*- C++ -*-===//
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
/// \file logging.h
/// \brief Declarations of the logging-related utility functions.
/// \author Antti Kivi
/// \date 11 September 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_LOGGING_H
#define ANTHEM_LOGGING_H

#include <memory>
#include <type_traits>

#include <spdlog/spdlog.h>

namespace anthem
{
  ///
  /// \brief Type of objects which do logging.
  ///
  using logger_t = std::shared_ptr<spdlog::logger>;

  ///
  /// \brief The main logger of the game.
  ///
  extern logger_t logger;

  ///
  /// \brief Creates a shared pointer to an object of the logger type provided
  /// by spdlog.
  ///
  /// \param name the name of the logger.
  /// \param pattern the formatting pattern of the logger.
  /// \param level the logging level of the logger.
  ///
  /// \return an \c std::shared_ptr<spdlog::logger>.
  ///
  const logger_t create_logger(
      const std::string& name,
      const std::string& pattern = "NONE",
      const spdlog::level::level_enum level = spdlog::level::info);

  // Logging methods which take the logger as a parameter.
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
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void trace(
        const logger_t& logger,
        const char* fmt,
        const Args&... args)
    {
      logger->trace(fmt, args...);
    }

    ///
    /// \brief Writes a trace-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <class T> inline void trace(const logger_t& logger, const T& msg)
    {
      logger->trace(msg);
    }

    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void debug(
        const logger_t& logger,
        const char* fmt,
        const Args&... args)
    {
      logger->debug(fmt, args...);
    }

    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <class T> inline void debug(const logger_t& logger, const T& msg)
    {
      logger->debug(msg);
    }

    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void info(
        const logger_t& logger,
        const char* fmt,
        const Args&... args)
    {
      logger->info(fmt, args...);
    }

    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <class T> inline void info(const logger_t& logger, const T& msg)
    {
      logger->info(msg);
    }

    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void warn(
        const logger_t& logger,
        const char* fmt,
        const Args&... args)
    {
      logger->warn(fmt, args...);
    }

    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <class T> inline void warn(const logger_t& logger, const T& msg)
    {
      logger->warn(msg);
    }

    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void error(
        const logger_t& logger,
        const char* fmt,
        const Args&... args)
    {
      logger->error(fmt, args...);
    }

    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <class T> inline void error(const logger_t& logger, const T& msg)
    {
      logger->error(msg);
    }

    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args types of the arguments in the formatting substitutions.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <class... Args>
    inline void critical(
        const logger_t& logger,
        const char* fmt,
        const Args&... args)
    {
      logger->critical(fmt, args...);
    }

    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This object is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T type of the log message.
    ///
    /// \param logger an object of type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <class T>
    inline void critical(const logger_t& logger, const T& msg)
    {
      logger->critical(msg);
    }

  } // namespace logging

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
    template <class... Args>
    inline void trace(const char* fmt, const Args&... args)
    {
      logger->trace(fmt, args...);
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
    template <class T> inline void trace(const T& msg)
    {
      logger->trace(msg);
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
    template <class... Args>
    inline void debug(const char* fmt, const Args&... args)
    {
      logger->debug(fmt, args...);
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
    template <class T> inline void debug(const T& msg)
    {
      logger->debug(msg);
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
    template <class... Args>
    inline void info(const char* fmt, const Args&... args)
    {
      logger->info(fmt, args...);
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
    template <class T> inline void info(const T& msg)
    {
      logger->info(msg);
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
    template <class... Args>
    inline void warn(const char* fmt, const Args&... args)
    {
      logger->warn(fmt, args...);
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
    template <class T> inline void warn(const T& msg)
    {
      logger->warn(msg);
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
    template <class... Args>
    inline void error(const char* fmt, const Args&... args)
    {
      logger->error(fmt, args...);
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
    template <class T> inline void error(const T& msg)
    {
      logger->error(msg);
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
    template <class... Args>
    inline void critical(const char* fmt, const Args&... args)
    {
      logger->critical(fmt, args...);
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
    template <class T>
    inline void critical(const T& msg)
    {
      logger->critical(msg);
    }

  } // namespace logging
} // namespace anthem

#endif // !ANTHEM_LOGGING_H
