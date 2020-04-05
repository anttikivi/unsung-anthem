/// The declaration of the type of the graphics system scenes.
/// \file
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_GRAPHICS_GRAPHICS_SCENE_H
#define ODE_SYSTEMS_GRAPHICS_GRAPHICS_SCENE_H

#include "ode/systems/scene.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// The type of the graphics system scene objects.
  ///
  class graphics_scene final : public scene
  {
  public:
    ///
    /// The system type of this scene.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// Constructs an object of the type \c graphics_scene.
    ///
    graphics_scene() = default;

    ///
    /// Constructs an object of the type \c graphics_scene by copying the given
    /// object of the type \c graphics_scene.
    ///
    /// \param a a \c graphics_scene from which the new one is constructed.
    ///
    graphics_scene(const graphics_scene& a) = default;

    ///
    /// Constructs an object of the type \c graphics_scene by moving the given
    /// object of the type \c graphics_scene.
    ///
    /// \param a a \c graphics_scene from which the new one is constructed.
    ///
    graphics_scene(graphics_scene&& a) = default;

    ///
    /// Destructs an object of the type \c graphics_scene.
    ///
    ~graphics_scene() = default;

    ///
    /// Assigns the given object of the type \c graphics_scene to this one by
    /// copying.
    ///
    /// \param a a \c graphics_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_scene& operator=(const graphics_scene& a) = default;

    ///
    /// Assigns the given object of the type \c graphics_scene to this one by
    /// moving.
    ///
    /// \param a a \c graphics_scene from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_scene& operator=(graphics_scene&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_GRAPHICS_SCENE_H
