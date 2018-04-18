//===------------------------------ scene.h ---------------------*- C++ -*-===//
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
/// \file scene.h
/// \brief Declaration of base type of system scene implementations of Obliging
/// Ode.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SCENE_H
#define ODE_SCENE_H

namespace ode
{
  ///
  /// \brief Base type of objects which implement functionalities of different
  /// system scenes.
  ///
  struct scene
  {
    ///
    /// \brief Destructs an object of type \c scene.
    ///
    virtual ~scene() = default;
  };

} // namespace ode

#endif // !ODE_SCENE_H
