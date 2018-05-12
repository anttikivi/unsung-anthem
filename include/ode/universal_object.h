//===------------------------- universal_object.h ---------------*- C++ -*-===//
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
/// \file universal_object.h
/// \brief Declaration of universal object of Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_UNIVERSAL_OBJECT_H
#define ODE_UNIVERSAL_OBJECT_H

#include <vector>

namespace ode
{
  class object_t;
} // namespace ode

namespace ode
{
  ///
  /// \class universal_object
  /// \brief Type of objects which hold functional system objects of Obliging
  /// Ode.
  ///
  class universal_object final
  {
  public:
    ///
    /// \brief Constructs an object of type \c universal_object.
    ///
    universal_object() = default;

    ///
    /// \brief Constructs an object of type \c universal_object by copying the
    /// given object of type \c universal_object.
    ///
    /// \param a \c universal_object from which the new one is constructed.
    ///
    universal_object(const universal_object& a) = default;

    ///
    /// \brief Constructs an object of type \c universal_object by moving the
    /// given object of type \c universal_object.
    ///
    /// \param a \c universal_object from which the new one is constructed.
    ///
    universal_object(universal_object&& a) = default;

    ///
    /// \brief Destructs an object of type \c universal_object.
    ///
    ~universal_object() = default;

    ///
    /// \brief Assigns the given object of type \c universal_object to this one
    /// by copying.
    ///
    /// \param a \c universal_object from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    universal_object& operator=(const universal_object& a) = default;

    ///
    /// \brief Assigns the given object of type \c universal_object to this one
    /// by moving.
    ///
    /// \param a \c universal_object from which this one is assigned.
    ///
    /// \return Reference to \c *this.
    ///
    universal_object& operator=(universal_object&& a) = default;

  private:
    ///
    /// \brief Objects which implement the different functionalities of
    /// systems.
    ///
    std::vector<object_t> objects;
  };
} // namespace ode

#endif // !ODE_UNIVERSAL_OBJECT_H
