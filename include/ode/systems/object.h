//===------------------------------ object.h --------------------*- C++ -*-===//
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
/// \file object.h
/// \brief The declaration of the base type of the system object
/// implementations.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_OBJECT_H
#define ODE_SYSTEMS_OBJECT_H

namespace ode
{
  ///
  /// \struct object
  /// \brief The base type of the objects which implement the functionalities
  /// of the different system objects.
  ///
  struct object
  {
    ///
    /// \brief Destructs an object of the type \c object.
    ///
    virtual ~object() = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_OBJECT_H
