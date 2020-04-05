/// The declaration of the base type of the system objects.
/// \file
/// \author Antti Kivi
/// \date 17 April 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ODE_SYSTEMS_SYSTEM_H
#define ODE_SYSTEMS_SYSTEM_H

#include "ode/systems/scene_configuration_t.h"
#include "ode/systems/scene_t.h"

namespace ode
{
  ///
  /// The base type of the objects which implement the functionalities of the
  /// different systems.
  ///
  class system
  {
  public:
    ///
    /// Constructs an object of the type \c system.
    ///
    system() = default;

    ///
    /// Constructs an object of the type \c system by copying the given object
    /// of the type \c system.
    ///
    /// \param a a \c system from which the new one is constructed.
    ///
    system(const system& a) = delete;

    ///
    /// Constructs an object of the type \c system by moving the given object
    /// of the type \c system.
    ///
    /// \param a a \c system from which the new one is constructed.
    ///
    system(system&& a) = default;

    ///
    /// Destructs an object of the type \c system.
    ///
    virtual ~system() = default;

    ///
    /// Assigns the given object of the type \c system to this one by copying.
    ///
    /// \param a a \c system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system& operator=(const system& a) = delete;

    ///
    /// Assigns the given object of the type \c system to this one by moving.
    ///
    /// \param a a \c system from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    system& operator=(system&& a) = default;

    ///
    /// Creates a scene object implementing the functionalities of this system.
    ///
    /// \param cfg the scene configuration according to which the scene is
    /// constructed.
    ///
    /// \return An object of the type \c scene_t.
    ///
    virtual scene_t make_scene(const scene_configuration_t& cfg) const = 0;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SYSTEM_H
