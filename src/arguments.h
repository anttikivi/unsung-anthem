//===--- arguments.h --------------------------------------------*- C++ -*-===//
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

#include <array>
#include <type_traits>

#include "anthem/std/optional.h"
#include "anthem/array.h"
#include "anthem/types.h"

namespace anthem {

  ///
  /// \struct arguments
  /// \brief Type of objects which hold parsed information of command line
  /// arguments.
  ///
  struct arguments final {
    ///
    /// \brief Constructs an object of class \c arguments with no data.
    ///
    arguments() noexcept = default;

    ///
    /// \brief Constructs an object of class \c arguments.
    ///
    /// \param window_width value of the starting width of the window.
    /// \param window_height value of the starting height of the window.
    ///
    constexpr arguments(const pixel_count window_width,
                        const pixel_count window_height) noexcept
        : window_width{window_width}, window_height{window_height} {

    }

    ///
    /// \brief Constructs an object of class \c arguments which has the same
    /// values as the original object \c a.
    ///
    /// \param a object from which values are copied into the constructed
    /// object.
    ///
    constexpr arguments(const arguments& a) noexcept = default;

    ///
    /// \brief Constructs an object of class \c arguments and moves the values
    /// of \c a to the constructed object.
    ///
    /// \param a object from which values are moved into the constructed object.
    ///
    constexpr arguments(arguments&& a) noexcept = default;

    ///
    /// \brief Destructs an object of class \c arguments.
    ///
    ~arguments() noexcept = default;

    ///
    /// \brief Copies the values of \c a and replaces the values of \c *this by
    /// them.
    ///
    /// \param a object of class \c arguments from which the values are copied.
    /// \return Reference to \c *this.
    ///
    constexpr arguments& operator=(const arguments& a) const noexcept = default;

    ///
    /// \brief Moves the values of \c a and replaces the values of \c *this by
    /// them.
    ///
    /// \param a object of class \c arguments from which the values are moved.
    /// \return Reference to \c *this.
    ///
    constexpr arguments& operator=(arguments&& a) const noexcept = default;

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
  /// \param lhs
  /// \param rhs
  /// \return \c true if the member values of the parameters are equal,
  /// otherwise \c false.
  ///
  constexpr bool operator==(const arguments& lhs,
                            const arguments& rhs) noexcept {

    return lhs.window_width == rhs.window_width &&
           lhs.window_height == rhs.window_height;
  }

  ///
  /// \brief Returns an object of class \c arguments which contains the values
  /// set when executing the program from the command line.
  ///
  /// \param args array containing the arguments passed to the program.
  /// \return An object of class \c std::experimental::optional which may
  /// contain an object of class \c arguments.
  ///
  template <std::size_t N>
  constexpr const optional<arguments>
  parse_arguments(const std::array<const char*, N> args) noexcept {

    return arguments{};
  }
}

#endif // !ANTHEM_ARGUMENTS_H
