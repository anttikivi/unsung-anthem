/// The declaration of the application type.
/// \file
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (c) 2018–2020 Antti Kivi.
/// Licensed under the Effective Elegy Licence.

#ifndef ANTHEM_APPLICATION_H
#define ANTHEM_APPLICATION_H

#include <vector>

#include "ode/systems/scene_configuration_t.h"
#include "ode/systems/system_t.h"
#include "ode/systems/system_type.h"

namespace anthem
{
  ///
  /// The type of the object which represents the application.
  ///
  class application final
  {
  public:
    ///
    /// Constructs an object of the type \c application.
    ///
    application() = default;

    ///
    /// Constructs an object of the type \c application by copying the given
    /// object of the type \c application.
    ///
    /// \param an \c application from which the new one is constructed.
    ///
    application(const application& a) = default;

    ///
    /// Constructs an object of the type \c application by moving the given
    /// object of the type \c application.
    ///
    /// \param an \c application from which the new one is constructed.
    ///
    application(application&& a) = default;

    ///
    /// Destructs an object of the type \c application.
    ///
    ~application() = default;

    ///
    /// Assigns the given object of the type \c application to this one by
    /// copying.
    ///
    /// \param a an \c application from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    application& operator=(const application& a) = default;

    ///
    /// Assigns the given object of the type \c application to this one by
    /// moving.
    ///
    /// \param a an \c application from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    application& operator=(application&& a) = default;

    ///
    /// Creates the application-specific instance of the requested system type.
    ///
    /// Remarks: The systems with the system type ‘other’ cannot be created
    /// with this function.
    ///
    /// \param type the type of the system which should be made.
    ///
    /// \return An object of the type \c ode::system_t which holds the system
    /// instance.
    ///
    ode::system_t make_system(const ode::system_type type);

    ///
    /// Creates the application-specific systems.
    ///
    /// \return A vector containing the system instances of the other systems.
    ///
    std::vector<ode::system_t> make_other_systems();

    ///
    /// Gives the configuration for the first scene that is created.
    ///
    /// \return An object of the type \c ode::scene_configuration_t.
    ///
    ode::scene_configuration_t first_scene() const;
  };

} // namespace anthem

#endif // !ANTHEM_APPLICATION_H
