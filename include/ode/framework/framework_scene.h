/// The declaration of the framework scene.
/// \file
/// \author Antti Kivi
/// \date 18 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_FRAMEWORK_FRAMEWORK_SCENE_H
#define ODE_FRAMEWORK_FRAMEWORK_SCENE_H

#include <vector>

#include "ode/systems/scene_configuration_t.h"
#include "ode/systems/scene_t.h"
#include "ode/systems/system_t.h"

namespace ode
{
  ///
  /// The type of the objects which hold the functional system scenes.
  ///
  class framework_scene final
  {
  public:
    ///
    /// The type of the references to the scenes.
    ///
    using scene_reference = scene_t&;

    ///
    /// Constructs an object of the type \c framework_scene.
    ///
    framework_scene() = default;

    ///
    /// Constructs an object of the type \c framework_scene.
    ///
    /// \param cfg the scene configuration according to which the scene is
    /// constructed.
    ///
    framework_scene(const scene_configuration_t& cfg);

    ///
    /// Constructs an object of the type \c framework_scene by copying the
    /// given object of the type \c framework_scene.
    ///
    /// \param a a \c framework_scene from which the new one is constructed.
    ///
    framework_scene(const framework_scene& a) = delete;

    ///
    /// Constructs an object of the type \c framework_scene by moving the given
    /// object of the type \c framework_scene.
    ///
    /// \param a a \c framework_scene from which the new one is constructed.
    ///
    framework_scene(framework_scene&& a) = default;

    ///
    /// Destructs an object of the type \c framework_scene.
    ///
    ~framework_scene() = default;

    ///
    /// Assigns the given object of the type \c framework_scene to this one by
    /// copying.
    ///
    /// \param a a \c framework_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    framework_scene& operator=(const framework_scene& a) = delete;

    ///
    /// Assigns the given object of the type \c framework_scene to this one by
    /// moving.
    ///
    /// \param a a \c framework_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    framework_scene& operator=(framework_scene&& a) = default;

    ///
    /// Extends the framework scene with the functionalities of the given
    /// system by extending the scene with system-specific scene.
    ///
    /// \param sys the system with which the framework scene is extended.
    ///
    /// \return A reference to the created object of the type \c scene_t.
    ///
    scene_reference extend(const system_t& sys);

  private:
    ///
    /// The configuration of this scene.
    ///
    scene_configuration_t config;

    ///
    /// The scenes which implement the different functionalities of the
    /// systems.
    ///
    std::vector<scene_t> scenes;
  };
} // namespace ode

#endif // !ODE_FRAMEWORK_FRAMEWORK_SCENE_H
