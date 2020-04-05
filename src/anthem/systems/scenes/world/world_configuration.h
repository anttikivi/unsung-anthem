/// The declaration of the type of the scene configurations for the basic
/// gameplay scenes.
/// \file
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_SYSTEMS_SCENES_WORLD_WORLD_CONFIGURATION_H
#define ANTHEM_SYSTEMS_SCENES_WORLD_WORLD_CONFIGURATION_H

#include <string>

#include "ode/lua/state.h"
#include "ode/systems/scene_configuration.h"

namespace anthem
{
  ///
  /// The type of the objects which hold the configurations of the basic
  /// gameplay scenes.
  ///
  class world_configuration : public ode::scene_configuration
  {
  public:
    ///
    /// Constructs an object of the type \c world_configuration.
    ///
    world_configuration() = default;

    ///
    /// Constructs an object of the type \c world_configuration.
    ///
    /// \param n the name of the configuration.
    ///
    world_configuration(const std::string& n);

    ///
    /// Constructs an object of the type \c world_configuration by copying the
    /// given object of the type \c world_configuration.
    ///
    /// \param a a \c world_configuration from which the new one is
    /// constructed.
    ///
    world_configuration(const world_configuration& a) = default;

    ///
    /// Constructs an object of the type \c world_configuration by moving the
    /// given object of the type \c world_configuration.
    ///
    /// \param a a \c world_configuration from which the new one is
    /// constructed.
    ///
    world_configuration(world_configuration&& a) = default;

    ///
    /// Destructs an object of the type \c world_configuration.
    ///
    ~world_configuration() = default;

    ///
    /// Assigns the given object of the type \c world_configuration to this one
    /// by copying.
    ///
    /// \param a a \c world_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    world_configuration& operator=(const world_configuration& a) = default;

    ///
    /// Assigns the given object of the type \c world_configuration to this one
    /// by moving.
    ///
    /// \param a a \c world_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    world_configuration& operator=(world_configuration&& a) = default;

  private:
    ///
    /// The Lua state this configuration uses to load its data.
    ///
    ode::lua::state_t state;

    ///
    /// The name of the configuration.
    ///
    const std::string name;

    ///
    /// The width of the map in tiles.
    ///
    int width;

    ///
    /// The height of the map in tiles.
    ///
    int height;
  };

} // namespace anthem

#endif // !ANTHEM_SYSTEMS_SCENES_WORLD_WORLD_CONFIGURATION_H
