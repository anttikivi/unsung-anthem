//===------------------------------ object.h --------------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file object.h
/// \brief The declaration of the base type of the system object
/// implementations.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_OBJECT_H
#define ODE_SYSTEMS_OBJECT_H

namespace ode
{
  ///
  /// \class object
  /// \brief The base type of the objects which implement the functionalities
  /// of the different system objects.
  ///
  class object
  {
  public:
    ///
    /// \brief Constructs an object of the type \c object.
    ///
    object() = default;

    ///
    /// \brief Constructs an object of the type \c object by copying the given
    /// object of the type \c object.
    ///
    /// \param a a \c object from which the new one is constructed.
    ///
    object(const object& a) = default;

    ///
    /// \brief Constructs an object of the type \c object by moving the given
    /// object of the type \c object.
    ///
    /// \param a a \c object from which the new one is constructed.
    ///
    object(object&& a) = default;

    ///
    /// \brief Destructs an object of the type \c object.
    ///
    virtual ~object() = default;

    ///
    /// \brief Assigns the given object of the type \c object to this one by
    /// copying.
    ///
    /// \param a a \c object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    object& operator=(const object& a) = default;

    ///
    /// \brief Assigns the given object of the type \c object to this one by
    /// moving.
    ///
    /// \param a a \c object from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    object& operator=(object&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_OBJECT_H
