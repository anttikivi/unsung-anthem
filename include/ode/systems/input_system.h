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
/// \brief The declaration of the type of the input system object.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_INPUT_SYSTEM_H
#define ODE_SYSTEMS_INPUT_SYSTEM_H

#include "ode/systems/system_type.h"
#include "ode/systems/system.h"

namespace ode
{
  ///
  /// \struct input_system
  /// \brief The type of the input system object.
  ///
  struct input_system final : public ode::system
  {
    ///
    /// \brief The system type of this system.
    ///
    static constexpr system_type type = system_type::input;

    ///
    /// \brief Destructs an object of the type \c input_system.
    ///
    ~input_system() = default;

    ///
    /// \brief Creates a scene object containing the type \c input_scene.
    ///
    /// \return An object of the type \c scene_t.
    ///
    scene_t create_scene() const;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_INPUT_SYSTEM_H
