//===-------------------------- graphics_scene.h ----------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (c) 2019 Antti Kivi
// Licensed under GNU Affero General Public License v3.0
//
//===----------------------------------------------------------------------===//
//
///
/// \file graphics_scene.h
/// \brief The declaration of the type of the graphics system scenes.
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_GRAPHICS_GRAPHICS_SCENE_H
#define ODE_SYSTEMS_GRAPHICS_GRAPHICS_SCENE_H

#include "ode/systems/scene.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// \class graphics_scene
  /// \brief The type of the graphics system scene objects.
  ///
  class graphics_scene final : public scene
  {
  public:
    ///
    /// \brief The system type of this scene.
    ///
    static constexpr system_type type = system_type::graphics;
    
    ///
    /// \brief Constructs an object of the type \c graphics_scene.
    ///
    graphics_scene() = default;

    ///
    /// \brief Constructs an object of the type \c graphics_scene by copying
    /// the given object of the type \c graphics_scene.
    ///
    /// \param a a \c graphics_scene from which the new one is constructed.
    ///
    graphics_scene(const graphics_scene& a) = default;

    ///
    /// \brief Constructs an object of the type \c graphics_scene by moving the
    /// given object of the type \c graphics_scene.
    ///
    /// \param a a \c graphics_scene from which the new one is constructed.
    ///
    graphics_scene(graphics_scene&& a) = default;

    ///
    /// \brief Destructs an object of the type \c graphics_scene.
    ///
    ~graphics_scene() = default;

    ///
    /// \brief Assigns the given object of the type \c graphics_scene to this
    /// one by copying.
    ///
    /// \param a a \c graphics_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_scene& operator=(const graphics_scene& a) = default;

    ///
    /// \brief Assigns the given object of the type \c graphics_scene to this
    /// one by moving.
    ///
    /// \param a a \c graphics_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_scene& operator=(graphics_scene&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_GRAPHICS_SCENE_H
