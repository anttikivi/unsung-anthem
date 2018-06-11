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

#ifndef ODE_SYSTEMS_INPUT_INPUT_SCENE_H
#define ODE_SYSTEMS_INPUT_INPUT_SCENE_H

#include "ode/systems/scene.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// \class input_scene
  /// \brief The type of the input system scene objects.
  ///
  class input_scene : public scene
  {
  public:
    ///
    /// \brief The system type of this scene.
    ///
    static constexpr system_type type = system_type::input;

    ///
    /// \brief Constructs an object of the type \c input_scene.
    ///
    input_scene() = default;

    ///
    /// \brief Constructs an object of the type \c input_scene by copying the
    /// given object of the type \c input_scene.
    ///
    /// \param a a \c input_scene from which the new one is constructed.
    ///
    input_scene(const input_scene& a) = default;

    ///
    /// \brief Constructs an object of the type \c input_scene by moving the
    /// given object of the type \c input_scene.
    ///
    /// \param a a \c input_scene from which the new one is constructed.
    ///
    input_scene(input_scene&& a) = default;

    ///
    /// \brief Destructs an object of the type \c input_scene.
    ///
    ~input_scene() = default;

    ///
    /// \brief Assigns the given object of the type \c input_scene to this one
    /// by copying.
    ///
    /// \param a a \c input_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_scene& operator=(const input_scene& a) = default;

    ///
    /// \brief Assigns the given object of the type \c input_scene to this one
    /// by moving.
    ///
    /// \param a a \c input_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    input_scene& operator=(input_scene&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_INPUT_INPUT_SCENE_H
