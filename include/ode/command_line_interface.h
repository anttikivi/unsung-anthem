//===---------------------- command_line_interface.h ------------*- C++ -*-===//
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
/// \file command_line_interface.h
/// \brief The declarations of the utilities related to parsing command line
/// arguments.
/// \author Antti Kivi
/// \date 2 February 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_COMMAND_LINE_INTERFACE_H
#define ODE_COMMAND_LINE_INTERFACE_H

#include <type_traits>

#include "ode/args_array.h"
#include "ode/types.h"

#include <spdlog/fmt/ostr.h> // This must be included for the custom logger
                             // object to work.

namespace ode
{
  using namespace std::string_literals;

  ///
  /// \brief The default width of the window in pixels.
  ///
  constexpr auto default_window_width = 120_px;

  ///
  /// \brief The default height of the window in pixels.
  ///
  constexpr auto default_window_height = 120_px;

  ///
  /// \brief The default name of the window.
  ///
#ifdef ODE_WINDOW_NAME
  constexpr auto default_window_name = ODE_WINDOW_NAME;
#else
  constexpr auto default_window_name = "ode";
#endif // !defined(ODE_WINDOW_NAME)

  ///
  /// \struct arguments
  /// \brief Type of objects which hold parsed information of command line
  /// arguments.
  ///
  struct arguments final
  {
    ///
    /// \brief Whether or not the arguments are parsed correctly by the parsing
    /// function.
    ///
    const bool parsed = false;

    ///
    /// \brief The starting width of the window.
    ///
    const pixel_count window_width = 0_px;

    ///
    /// \brief The starting height of the window.
    ///
    const pixel_count window_height = 0_px;

    ///
    /// \brief The name of the window.
    ///
    const std::string window_name = "null"s;

  }; // struct arguments final

  ///
  /// \brief Compares the two objects of class \c arguments.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  constexpr auto operator==(const arguments& lhs, const arguments& rhs) noexcept
  {
    return lhs.parsed == rhs.parsed &&
        lhs.window_width == rhs.window_width &&
        lhs.window_height == rhs.window_height &&
        lhs.window_name == rhs.window_name;
  }

  ///
  /// \brief Compares the two objects of class \c arguments.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  constexpr auto operator!=(const arguments& lhs, const arguments& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  ///
  /// \brief Inserts the formatted data of an object of type \c arguments to
  /// the \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the object, the data of which is inserted.
  ///
  /// \return a reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const arguments& a);

  ///
  /// \brief Returns an object of class \c arguments which contains the values
  /// set when executing the program from the command line.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return An object of class \c arguments.
  ///
  arguments parse_arguments(const int argc, args_array argv[]) noexcept;

} // namespace ode

#endif // !ODE_COMMAND_LINE_INTERFACE_H
