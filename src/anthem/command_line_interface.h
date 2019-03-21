//===---------------------- command_line_interface.h ------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file command_line_interface.h
/// \brief The declarations of the utilities related to parsing command line
/// arguments.
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_COMMAND_LINE_INTERFACE_H
#define ANTHEM_COMMAND_LINE_INTERFACE_H

#include <string>

#include "ode/argv_t.h"
#include "ode/pixel_count.h"

#include <spdlog/fmt/ostr.h> // This must be included for the custom logger
                             // object to work.

namespace anthem
{
  using namespace std::literals::string_literals;

  ///
  /// \brief The default width of the window in pixels.
  ///
  constexpr auto default_window_width = 400_px;

  ///
  /// \brief The default height of the window in pixels.
  ///
  constexpr auto default_window_height = 240_px;

  ///
  /// \brief The default name of the window.
  ///
#ifdef ANTHEM_WINDOW_NAME
  constexpr auto default_window_name = ANTHEM_WINDOW_NAME;
#else
# ifdef ODE_WINDOW_NAME
  constexpr auto default_window_name = ODE_WINDOW_NAME;
# else
  constexpr auto default_window_name = "anthem";
# endif // !defined(ODE_WINDOW_NAME)
#endif // !defined(ANTHEM_WINDOW_NAME)

  ///
  /// \struct arguments
  /// \brief The type of the objects which hold the parsed information of
  /// command line arguments.
  ///
  struct arguments final
  {
    ///
    /// \brief Whether or not the arguments were parsed correctly by the
    /// parsing function.
    ///
    const bool parsed = false;

    ///
    /// \brief Whether or not the help message should be shown.
    ///
    const bool show_help = false;

    ///
    /// \brief The starting width of the window.
    ///
    const ode::pixel_count window_width = 0_px;

    ///
    /// \brief The starting height of the window.
    ///
    const ode::pixel_count window_height = 0_px;

    ///
    /// \brief The name of the window.
    ///
    const std::string window_name = "null"s;

  }; // struct arguments final

  ///
  /// \brief Compares two objects of the type \c arguments.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  constexpr auto operator==(
      const arguments& lhs,
      const arguments& rhs) noexcept
  {
    return lhs.parsed == rhs.parsed &&
        lhs.show_help == rhs.show_help && 
        lhs.window_width == rhs.window_width &&
        lhs.window_height == rhs.window_height &&
        lhs.window_name == rhs.window_name;
  }

  ///
  /// \brief Compares two objects of the type \c arguments.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  constexpr auto operator!=(
      const arguments& lhs,
      const arguments& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  ///
  /// \brief Inserts the formatted data of an object of the type \c arguments
  /// to the given \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the object, the data of which is inserted.
  ///
  /// \return A reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const arguments& a);

  ///
  /// \brief Returns an object of the type \c arguments which contains the
  /// values set when executing the program from the command line.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return An object of the type \c arguments.
  ///
  arguments parse_arguments(const int argc, ode::argv_t argv[]) noexcept;

} // namespace anthem

#endif // !ANTHEM_COMMAND_LINE_INTERFACE_H
