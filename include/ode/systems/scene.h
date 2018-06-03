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
/// \brief The declaration of the base type of the system scene
/// implementations.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SCENE_H
#define ODE_SYSTEMS_SCENE_H

namespace ode
{
  ///
  /// \brief The base type of the objects which implement the functionalities
  /// of the different system scenes.
  ///
  struct scene
  {
    ///
    /// \brief Destructs an object of the type \c scene.
    ///
    virtual ~scene() = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SCENE_H
