//===--------------------------- application.h ------------------*- C++ -*-===//
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
/// \file application.h
/// \brief The declaration of the application type.
/// \author Antti Kivi
/// \date 10 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ANTHEM_APPLICATION_H
#define ANTHEM_APPLICATION_H

#include <vector>

#include "ode/systems/scene_configuration_t.h"
#include "ode/systems/system_t.h"
#include "ode/systems/system_type.h"

namespace anthem
{
  ///
  /// \class application
  /// \brief The type of the object which represents the application.
  ///
  class application final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c application.
    ///
    application() = default;

    ///
    /// \brief Constructs an object of the type \c application by copying the
    /// given object of the type \c application.
    ///
    /// \param an \c application from which the new one is constructed.
    ///
    application(const application& a) = default;

    ///
    /// \brief Constructs an object of the type \c application by moving the
    /// given object of the type \c application.
    ///
    /// \param an \c application from which the new one is constructed.
    ///
    application(application&& a) = default;

    ///
    /// \brief Destructs an object of the type \c application.
    ///
    ~application() = default;

    ///
    /// \brief Assigns the given object of the type \c application to this one
    /// by copying.
    ///
    /// \param a an \c application from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    application& operator=(const application& a) = default;

    ///
    /// \brief Assigns the given object of the type \c application to this one
    /// by moving.
    ///
    /// \param a an \c application from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    application& operator=(application&& a) = default;

    ///
    /// \brief Creates the application-specific instance of the requested
    /// system type.
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
    /// \brief Creates the application-specific systems.
    ///
    /// \return A vector containing the system instances of the other systems.
    ///
    std::vector<ode::system_t> make_other_systems();

    ///
    /// \brief Gives the configuration for the first scene that is created.
    ///
    /// \return An object of the type \c ode::scene_configuration_t.
    ///
    ode::scene_configuration_t first_scene() const;
  };

} // namespace anthem

#endif // !ANTHEM_APPLICATION_H
