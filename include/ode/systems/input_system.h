//===--------------------------- input_system.h -----------------*- C++ -*-===//
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
/// \file input_system.h
/// \brief The declaration of the type of the input system.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_INPUT_SYSTEM_H
#define ODE_SYSTEMS_INPUT_SYSTEM_H

#include "ode/systems/system.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// \class input_system
  /// \brief The type of the input system.
  ///
  class input_system : public system
  {
  public:
    ///
    /// \brief The system type of this system.
    ///
    static constexpr system_type type = system_type::input;

    ///
    /// \brief Constructs an object of the type \c input_system.
    ///
    input_system() = default;

    ///
    /// \brief Constructs an object of the type \c input_system by copying the
    /// given object of the type \c input_system.
    ///
    /// \param a a \c input_system from which the new one is constructed.
    ///
    input_system(const input_system& a) = delete;

    ///
    /// \brief Constructs an object of the type \c input_system by moving the
    /// given object of the type \c input_system.
    ///
    /// \param a a \c input_system from which the new one is constructed.
    ///
    input_system(input_system&& a) = default;

    ///
    /// \brief Destructs an object of the type \c input_system.
    ///
    ~input_system() = default;

    ///
    /// \brief Assigns the given object of the type \c input_system to this one
    /// by copying.
    ///
    /// \param a a \c input_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_system& operator=(const input_system& a) = delete;

    ///
    /// \brief Assigns the given object of the type \c input_system to this one
    /// by moving.
    ///
    /// \param a a \c input_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_system& operator=(input_system&& a) = default;

    ///
    /// \brief Creates a scene containing the type \c input_scene.
    ///
    /// \return An object of the type \c scene_t.
    ///
    scene_t create_scene() const;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_INPUT_SYSTEM_H
