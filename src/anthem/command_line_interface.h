/// The declarations of the utilities related to parsing command line
/// arguments.
/// \file
/// \author Antti Kivi
/// \date 29 March 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_COMMAND_LINE_INTERFACE_H
#define ANTHEM_COMMAND_LINE_INTERFACE_H

#include <string>
#include <utility>

// This must be included for the custom logger object to work.
#include <spdlog/fmt/ostr.h>

#include "ode/pixel_t.h"

namespace anthem
{
  using namespace std::literals::string_literals;
  using namespace ode::literals::number_literals;

  //===--------------------------------------------------------------------===//
  //===--- Default literal values -----------------------------------------===//
  //===--------------------------------------------------------------------===//

  ///
  /// The default initial width of the window in pixels.
  ///
  constexpr auto default_window_width = 400_px;

  ///
  /// The default initial height of the window in pixels.
  ///
  constexpr auto default_window_height = 240_px;

  ///
  /// The default name of the window.
  ///
#ifdef ANTHEM_WINDOW_NAME
  constexpr auto default_window_name = ANTHEM_WINDOW_NAME;
#else
#  ifdef ODE_WINDOW_NAME
  constexpr auto default_window_name = ODE_WINDOW_NAME;
#  else
  constexpr auto default_window_name = "anthem";
#  endif // !defined(ODE_WINDOW_NAME)
#endif // !defined(ANTHEM_WINDOW_NAME)

  //===--------------------------------------------------------------------===//
  //===--- Default values for command line options ------------------------===//
  //===--------------------------------------------------------------------===//

  ///
  /// The default value passed for the the command line option for the initial
  /// width of the window in pixels.
  ///
  constexpr auto default_window_width_value = "400";

  ///
  /// The default value passed for the the command line option for the initial
  /// height of the window in pixels.
  ///
  constexpr auto default_window_height_value = "240";

  ///
  /// The default value passed for the the command line option for the name of
  /// the window.
  ///
  constexpr auto default_window_name_value = default_window_name;

  ///
  /// The type of the objects which hold the parsed information of command line
  /// arguments.
  ///
  struct arguments final
  {
    ///
    /// The starting width of the window.
    ///
    const ode::pixel_t window_width = 0_px;

    ///
    /// The starting height of the window.
    ///
    const ode::pixel_t window_height = 0_px;

    ///
    /// The name of the window.
    ///
    const std::string window_name = "null"s;

  }; // struct arguments final

  ///
  /// Compares two objects of the type \c arguments.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  constexpr auto operator==(const arguments& lhs, const arguments& rhs) noexcept
  {
    return lhs.window_width == rhs.window_width &&
        lhs.window_height == rhs.window_height &&
        lhs.window_name == rhs.window_name;
  }

  ///
  /// Compares two objects of the type \c arguments.
  ///
  /// \param lhs the left-hand side object of the operator.
  /// \param rhs the right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are not equal,
  /// otherwise \c false.
  ///
  constexpr auto operator!=(const arguments& lhs, const arguments& rhs) noexcept
  {
    return !(lhs == rhs);
  }

  ///
  /// Inserts the formatted data of an object of the type \c arguments to the
  /// given \c std::ostream.
  ///
  /// \param os the stream to which the data is inserted.
  /// \param a the object, the data of which is inserted.
  ///
  /// \return A reference of the \c std::ostream.
  ///
  std::ostream& operator<<(std::ostream& os, const arguments& a);

  ///
  /// Returns an object of the type \c std::pair, the first element of which
  /// contains a Boolean value telling whether the command line arguments were
  /// parsed properly and the second element of which contains an object of the
  /// type \c arguments which contains the values set when executing the program
  /// from the command line.
  ///
  /// \param argc the number of arguments passed in the execution.
  /// \param argv the array containing the arguments passed in the execution.
  ///
  /// \return An object of the type \c std::pair.
  ///
  std::pair<bool, arguments> parse_arguments(
      const int argc, char* argv[]) noexcept;

} // namespace anthem

#endif // !ANTHEM_COMMAND_LINE_INTERFACE_H
