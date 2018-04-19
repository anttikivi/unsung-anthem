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
/// \brief Declaration of type of input system object of Obliging Ode.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_INPUT_SYSTEM_H
#define ODE_INPUT_SYSTEM_H

#include "ode/system_type.h"
#include "ode/system.h"

namespace ode
{
  ///
  /// \brief Type of input system object.
  ///
  struct input_system final : public ode::system
  {
    ///
    /// \brief The system type of this system.
    ///
    static constexpr system_type type = system_type::input;

    ///
    /// \brief Destructs an object of type \c input_system.
    ///
    ~input_system() = default;

    ///
    /// \brief Creates a scene object containing the type \c input_scene.
    ///
    /// \return An object of type \c scene_t.
    ///
    scene_t create_scene() const;
  };

} // namespace ode

#endif // !ODE_INPUT_SYSTEM_H
