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
/// \brief Declaration of base type of system object implementations of
/// Obliging Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_OBJECT_H
#define ODE_OBJECT_H

namespace ode
{
  ///
  /// \brief Base type of objects which implement functionalities of different
  /// system objects.
  ///
  struct object
  {
    ///
    /// \brief Destructs an object of type \c object.
    ///
    virtual ~object() = default;
  };

} // namespace ode

#endif // !ODE_OBJECT_H
