/// The declarations of the logging-related utility functions.
/// \file
/// \author Antti Kivi
/// \date 31 January 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_LOGGING_H
#define ODE_LOGGING_H

#include <memory>

#include <spdlog/spdlog.h>

namespace ode
{
  ///
  /// The the type of the objects which do logging.
  ///
  using logger_t = std::shared_ptr<spdlog::logger>;

  namespace detail
  {
    ///
    /// Creates a shared pointer to an object of the logger the type.
    ///
    /// \param name the name of the logger.
    /// \param sink the sink to be used in the logger.
    ///
    /// \return an \c std::shared_ptr<spdlog::logger>.
    ///
    logger_t make_logger(const std::string& name, const spdlog::sink_ptr sink);

  } // namespace detail

  ///
  /// Creates a shared pointer to an object of the logger the type provided by
  /// spdlog.
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
    /// Writes a trace-level log message into the logger.
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
    template <typename... Args> inline void trace(
        const logger_t& logger, const char* fmt, const Args&... args)
    {
      logger->trace(fmt, args...);
    }

    ///
    /// Writes a trace-level log message into the logger.
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
    /// Writes a debug-level log message into the logger.
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
    template <typename... Args> inline void debug(
        const logger_t& logger, const char* fmt, const Args&... args)
    {
      logger->debug(fmt, args...);
    }

    ///
    /// Writes a debug-level log message into the logger.
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
    /// Writes an info-level log message into the logger.
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
    template <typename... Args> inline void info(
        const logger_t& logger, const char* fmt, const Args&... args)
    {
      logger->info(fmt, args...);
    }

    ///
    /// Writes an info-level log message into the logger.
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
    template <typename T> inline void info(const logger_t& logger, const T& msg)
    {
      logger->info(msg);
    }

    ///
    /// Writes a warning-level log message into the logger.
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
    template <typename... Args> inline void warn(
        const logger_t& logger, const char* fmt, const Args&... args)
    {
      logger->warn(fmt, args...);
    }

    ///
    /// Writes a warning-level log message into the logger.
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
    template <typename T> inline void warn(const logger_t& logger, const T& msg)
    {
      logger->warn(msg);
    }

    ///
    /// Writes an error-level log message into the logger.
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
    template <typename... Args> inline void error(
        const logger_t& logger, const char* fmt, const Args&... args)
    {
      logger->error(fmt, args...);
    }

    ///
    /// Writes an error-level log message into the logger.
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
    /// Writes a critical-level log message into the logger.
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
    template <typename... Args> inline void critical(
        const logger_t& logger, const char* fmt, const Args&... args)
    {
      logger->critical(fmt, args...);
    }

    ///
    /// Writes a critical-level log message into the logger.
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
