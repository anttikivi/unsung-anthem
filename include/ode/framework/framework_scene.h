//===------------------------- framework_scene.h ----------------*- C++ -*-===//
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
/// \file framework_scene.h
/// \brief The declaration of the framework scene.
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_FRAMEWORK_FRAMEWORK_SCENE_H
#define ODE_FRAMEWORK_FRAMEWORK_SCENE_H

#include <vector>

#include "ode/systems/scene_configuration.h"
#include "ode/systems/scene_t.h"
#include "ode/systems/system_t.h"

namespace ode
{
  ///
  /// \class framework_scene
  /// \brief The type of the objects which hold the functional system scenes.
  ///
  class framework_scene final
  {
  public:
    ///
    /// \brief The type of the references to the scenes.
    /// 
    using scene_reference = scene_t&;

    ///
    /// \brief Constructs an object of the type \c framework_scene.
    ///
    framework_scene();

    ///
    /// \brief Constructs an object of the type \c framework_scene by copying
    /// the given object of the type \c framework_scene.
    ///
    /// \param a a \c framework_scene from which the new one is constructed.
    ///
    framework_scene(const framework_scene& a) = default;

    ///
    /// \brief Constructs an object of the type \c framework_scene by moving
    /// the given object of the type \c framework_scene.
    ///
    /// \param a a \c framework_scene from which the new one is constructed.
    ///
    framework_scene(framework_scene&& a) = default;

    ///
    /// \brief Destructs an object of the type \c framework_scene.
    ///
    ~framework_scene() = default;

    ///
    /// \brief Assigns the given object of the type \c framework_scene to this
    /// one by copying.
    ///
    /// \param a a \c framework_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    framework_scene& operator=(const framework_scene& a) = default;

    ///
    /// \brief Assigns the given object of the type \c framework_scene to this
    /// one by moving.
    ///
    /// \param a a \c framework_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    framework_scene& operator=(framework_scene&& a) = default;

    ///
    /// \brief Extends the framework scene with the functionalities of the
    /// given system by extending the scene with system-specific scene.
    ///
    /// \param sys the system with which the framework scene is extended.
    ///
    /// \return A reference to the created object of the type \c scene_t.
    ///
    scene_reference extend(const system_t& sys);

  private:
    ///
    /// \brief The configuration of this scene.
    ///
    scene_configuration config;

    ///
    /// \brief The scenes which implement the different functionalities of the
    /// systems.
    ///
    std::vector<scene_t> scenes;
  };
} // namespace ode

#endif // !ODE_FRAMEWORK_FRAMEWORK_SCENE_H
