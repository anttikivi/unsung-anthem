//===------------------------- arguments.h ----------------------*- C++ -*-===//
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
/// \file arguments.h
/// \brief The declarations of the utilities related to parsing command line
/// arguments.
/// \author Antti Kivi
/// \date 14 July 2017
/// \copyright Copyright (c) 2017 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_ARGUMENTS_H
#define ANTHEM_ARGUMENTS_H

#include <type_traits>

#include "anthem/logging.h"
#include "anthem/types.h"

#include "gsl/assert"

namespace anthem {

  ///
  /// \struct arguments
  /// \brief Type of objects which hold parsed information of command line
  /// arguments.
  ///
  struct arguments final {

    ///
    /// \brief Whether or not the arguments are parsed correctly.
    ///
    const bool is_parsed{false};

    ///
    /// \brief The starting width of the window.
    ///
    const pixel_count window_width{0};

    ///
    /// \brief The starting height of the window.
    ///
    const pixel_count window_height{0};
  };

  ///
  /// \brief Compares the two objects of class \c arguments.
  ///
  /// \param lhs left-hand side object of the operator.
  /// \param rhs right-hand side object of the operator.
  ///
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  constexpr const bool operator==(const arguments& lhs,
                                  const arguments& rhs) noexcept {

    return lhs.is_parsed == rhs.is_parsed &&
           lhs.window_width == rhs.window_width &&
           lhs.window_height == rhs.window_height;
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
  constexpr const bool operator!=(const arguments& lhs,
                                  const arguments& rhs) noexcept {

    return !(lhs == rhs);
  }

  ///
  /// \brief Returns an object of class \c arguments which contains the values
  /// set when executing the program from the command line.
  ///
  /// \param logger the main logger.
  /// \param argc the number of arguments passed in the execution.
  /// \param argv array containing the arguments passed in the execution.
  ///
  /// \return An object of class \c arguments.
  ///
  const arguments parse_arguments(const logging::logger_t& logger,
                                  const int argc, const char* argv[]) noexcept;

} // namespace anthem

#endif // !ANTHEM_ARGUMENTS_H
