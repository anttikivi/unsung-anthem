//===----------------------------- logging.h --------------------*- C++ -*-===//
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
/// \file logging.h
/// \brief The declarations of the logging-related utility functions.
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_LOGGING_H
#define ODE_LOGGING_H

#include <memory>
#include <type_traits>

#include <spdlog/spdlog.h>

namespace ode
{
  ///
  /// \brief The the type of the objects which do logging.
  ///
  using logger_t = std::shared_ptr<spdlog::logger>;

  namespace detail
  {
    ///
    /// \brief Creates a shared pointer to an object of the logger the type.
    ///
    /// \param name the name of the logger.
    /// \param sink the sink to be used in the logger.
    ///
    /// \return an \c std::shared_ptr<spdlog::logger>.
    ///
    logger_t make_logger(const std::string& name, const spdlog::sink_ptr sink);

  } // namespace detail

  ///
  /// \brief Creates a shared pointer to an object of the logger the type provided
  /// by spdlog.
  ///
  /// \param name the name of the logger.
  /// \param pattern the formatting pattern of the logger.
  /// \param level the logging level of the logger.
  /// \param sink the sink to be used in the logger.
  ///
  /// \return an \c std::shared_ptr<spdlog::logger>.
  ///
  logger_t create_logger(
      const std::string& name,
      const std::string& pattern = "NONE",
      const spdlog::level::level_enum level = spdlog::level::trace,
      const spdlog::sink_ptr sink = nullptr);

  // Logging methods which take the logger as a parameter.
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
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
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
    /// \tparam T the type of the log message.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <typename T>
    inline void trace(const logger_t& logger, const T& msg)
    {
      logger->trace(msg);
    }

    ///
    /// \brief Writes a debug-level log message into the logger.
    ///
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
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
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <typename T>
    inline void debug(const logger_t& logger, const T& msg)
    {
      logger->debug(msg);
    }

    ///
    /// \brief Writes an info-level log message into the logger.
    ///
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
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
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <typename T>
    inline void info(const logger_t& logger, const T& msg)
    {
      logger->info(msg);
    }

    ///
    /// \brief Writes a warning-level log message into the logger.
    ///
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
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
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <typename T>
    inline void warn(const logger_t& logger, const T& msg)
    {
      logger->warn(msg);
    }

    ///
    /// \brief Writes an error-level log message into the logger.
    ///
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
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
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <typename T>
    inline void error(const logger_t& logger, const T& msg)
    {
      logger->error(msg);
    }

    ///
    /// \brief Writes a critical-level log message into the logger.
    ///
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam Args the types of the arguments in the formatting
    /// substitutions.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param fmt the format of the logger message.
    /// \param args the substitutions for the message format.
    ///
    template <typename... Args>
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
    /// Remarks: This function is impure as it writes into the logger. Thus, it
    /// does not return anything.
    ///
    /// \tparam T the type of the log message.
    ///
    /// \param logger an object of the type shared_ptr containing the logger
    /// object.
    /// \param msg the logger message.
    ///
    template <typename T>
    inline void critical(const logger_t& logger, const T& msg)
    {
      logger->critical(msg);
    }

  } // namespace logging
} // namespace ode

#endif // !ODE_LOGGING_H
