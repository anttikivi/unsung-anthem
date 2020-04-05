/// The declaration of the type of the graphics system.
/// \file
/// \author Antti Kivi
/// \date 8 May 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_GRAPHICS_GRAPHICS_SYSTEM_H
#define ODE_SYSTEMS_GRAPHICS_GRAPHICS_SYSTEM_H

#include "ode/systems/system.h"
#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// The type of the graphics system.
  ///
  /// The graphics system controls only the viewport inside the program window.
  ///
  class graphics_system : public system
  {
  public:
    ///
    /// The system type of this system.
    ///
    static constexpr system_type type = system_type::graphics;

    ///
    /// Constructs an object of the type \c graphics_system.
    ///
    graphics_system() = default;

    ///
    /// Constructs an object of the type \c graphics_system by copying the
    /// given object of the type \c graphics_system.
    ///
    /// \param a a \c graphics_system from which the new one is constructed.
    ///
    graphics_system(const graphics_system& a) = delete;

    ///
    /// Constructs an object of the type \c graphics_system by moving the given
    /// object of the type \c graphics_system.
    ///
    /// \param a a \c graphics_system from which the new one is constructed.
    ///
    graphics_system(graphics_system&& a) = default;

    ///
    /// Destructs an object of the type \c graphics_system.
    ///
    ~graphics_system() = default;

    ///
    /// Assigns the given object of the type \c graphics_system to this one by
    /// copying.
    ///
    /// \param a a \c graphics_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_system& operator=(const graphics_system& a) = delete;

    ///
    /// Assigns the given object of the type \c graphics_system to this one by
    /// moving.
    ///
    /// \param a a \c graphics_system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    graphics_system& operator=(graphics_system&& a) = default;

    ///
    /// Creates a scene object containing the type \c graphics_scene.
    ///
    /// \param cfg the scene configuration according to which the scene is
    /// constructed.
    ///
    /// \return An object of the type \c scene_t.
    ///
    scene_t make_scene(const scene_configuration_t& cfg) const;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_GRAPHICS_GRAPHICS_SYSTEM_H
