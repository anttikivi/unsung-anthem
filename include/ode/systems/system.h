//===------------------------------ system.h --------------------*- C++ -*-===//
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
/// \file system.h
/// \brief The declaration of the base type of the system objects.
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SYSTEM_H
#define ODE_SYSTEMS_SYSTEM_H

#include "ode/systems/scene_t.h"

namespace ode
{
  ///
  /// \class system
  /// \brief The base type of the objects which implement the functionalities
  /// of the different systems.
  ///
  class system
  {
  public:
    ///
    /// \brief Constructs an object of the type \c system.
    ///
    system() = default;

    ///
    /// \brief Constructs an object of the type \c system by copying the given
    /// object of the type \c system.
    ///
    /// \param a a \c system from which the new one is constructed.
    ///
    system(const system& a) = delete;

    ///
    /// \brief Constructs an object of the type \c system by moving the given
    /// object of the type \c system.
    ///
    /// \param a a \c system from which the new one is constructed.
    ///
    system(system&& a) = default;

    ///
    /// \brief Destructs an object of the type \c system.
    ///
    virtual ~system() = default;

    ///
    /// \brief Assigns the given object of the type \c system to this one by
    /// copying.
    ///
    /// \param a a \c system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system& operator=(const system& a) = delete;

    ///
    /// \brief Assigns the given object of the type \c system to this one by
    /// moving.
    ///
    /// \param a a \c system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system& operator=(system&& a) = default;

    ///
    /// \brief Creates a scene object implementing the functionalities of this
    /// system.
    ///
    /// \return An object of the type \c scene_t.
    ///
    virtual scene_t create_scene() const = 0;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SYSTEM_H
