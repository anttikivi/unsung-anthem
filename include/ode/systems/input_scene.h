//===--------------------------- input_scene.h ------------------*- C++ -*-===//
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
/// \file input_scene.h
/// \brief The declaration of the type of the input system scene.
/// \author Antti Kivi
/// \date 19 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_INPUT_SCENE_H
#define ODE_SYSTEMS_INPUT_SCENE_H

#include "ode/scene.h"
#include "ode/system_type.h"

namespace ode
{
  ///
  /// \struct input_scene
  /// \brief The type of the input system scene objects.
  ///
  struct input_scene final : public scene
  {
    ///
    /// \brief The system type of this scene.
    ///
    static constexpr system_type type = system_type::input;

    ///
    /// \brief Destructs an object of the type \c input_scene.
    ///
    ~input_scene() = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_INPUT_SCENE_H
