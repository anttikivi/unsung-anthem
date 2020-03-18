//===------------------------------ scene.h ---------------------*- C++ -*-===//
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
/// \file scene.h
/// \brief The declaration of the base type of the system scene
/// implementations.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SCENE_H
#define ODE_SYSTEMS_SCENE_H

namespace ode
{
  ///
  /// \class scene
  /// \brief The base type of the objects which implement the functionalities
  /// of the different system scenes.
  ///
  class scene
  {
  public:
    ///
    /// \brief Constructs an object of the type \c scene.
    ///
    scene() = default;

    ///
    /// \brief Constructs an object of the type \c scene by copying the given
    /// object of the type \c scene.
    ///
    /// \param a a \c scene from which the new one is constructed.
    ///
    scene(const scene& a) = default;

    ///
    /// \brief Constructs an object of the type \c scene by moving the given
    /// object of the type \c scene.
    ///
    /// \param a a \c scene from which the new one is constructed.
    ///
    scene(scene&& a) = default;

    ///
    /// \brief Destructs an object of the type \c scene.
    ///
    virtual ~scene() = default;

    ///
    /// \brief Assigns the given object of the type \c scene to this one by
    /// copying.
    ///
    /// \param a a \c scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene& operator=(const scene& a) = default;

    ///
    /// \brief Assigns the given object of the type \c scene to this one by
    /// moving.
    ///
    /// \param a a \c scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene& operator=(scene&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SCENE_H
