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

namespace anthem {

  ///
  /// \class arguments
  /// \brief Type of objects which hold parsed information of command line
  /// arguments.
  ///
  class arguments final {
  public:

    ///
    /// \brief Constructs an object of class \c arguments with no data.
    ///
    constexpr arguments() noexcept = default;

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
    constexpr ~arguments() noexcept = default;

    ///
    /// \brief Copies the values of \c a and replaces the values of \c *this by
    /// them.
    ///
    /// \param a object of class \c arguments from which the values are copied.
    /// \return Reference to \c *this.
    ///
    constexpr arguments& operator=(const arguments& a) noexcept = default;

    ///
    /// \brief Moves the values of \c a and replaces the values of \c *this by
    /// them.
    ///
    /// \param a object of class \c arguments from which the values are moved.
    /// \return Reference to \c *this.
    ///
    constexpr arguments& operator=(arguments&& a) noexcept = default;

  private:
  };

  

}

#endif // !ANTHEM_ARGUMENTS_H
