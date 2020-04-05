/// The declaration of the type of the scene configurations.
/// \file
/// \author Antti Kivi
/// \date 4 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_SCENE_CONFIGURATION_H
#define ODE_SYSTEMS_SCENE_CONFIGURATION_H

namespace ode
{
  ///
  /// The type of the objects which hold the configurations of the scenes which
  /// determine how a scene is loaded and run.
  ///
  class scene_configuration
  {
  public:
    ///
    /// Constructs an object of the type \c scene_configuration.
    ///
    scene_configuration() = default;

    ///
    /// Constructs an object of the type \c scene_configuration by copying the
    /// given object of the type \c scene_configuration.
    ///
    /// \param a a \c scene_configuration from which the new one is
    /// constructed.
    ///
    scene_configuration(const scene_configuration& a) = default;

    ///
    /// Constructs an object of the type \c scene_configuration by moving the
    /// given object of the type \c scene_configuration.
    ///
    /// \param a a \c scene_configuration from which the new one is
    /// constructed.
    ///
    scene_configuration(scene_configuration&& a) = default;

    ///
    /// Destructs an object of the type \c scene_configuration.
    ///
    virtual ~scene_configuration() = default;

    ///
    /// Assigns the given object of the type \c scene_configuration to this one
    /// by copying.
    ///
    /// \param a a \c scene_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration& operator=(const scene_configuration& a) = default;

    ///
    /// Assigns the given object of the type \c scene_configuration to this one
    /// by moving.
    ///
    /// \param a a \c scene_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration& operator=(scene_configuration&& a) = default;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SCENE_CONFIGURATION_H
