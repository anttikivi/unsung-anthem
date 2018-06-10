//===----------------------- scene_configuration.h --------------*- C++ -*-===//
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
/// \file scene_configuration.h
/// \brief The declaration of the type of the scene configurations.
/// \author Antti Kivi
/// \date 4 June 2018
/// \copyright Copyright (c) 2018 Venturesome Stone
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SCENES_SCENE_CONFIGURATION_H
#define ODE_SCENES_SCENE_CONFIGURATION_H

#include <vector>

#include "ode/systems/system_type.h"

namespace ode
{
  ///
  /// \class scene_configuration
  /// \brief The type of the objects which hold the configurations of the
  /// scenes which determine how a scene is loaded and run.
  ///
  class scene_configuration final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c scene_configuration.
    ///
    scene_configuration();

    ///
    /// \brief Constructs an object of the type \c scene_configuration.
    ///
    /// \param d a vector which contains the types of the systems which should
    /// be disabled.
    ///
    scene_configuration(const std::vector<system_type>& d);

    ///
    /// \brief Constructs an object of the type \c scene_configuration by
    /// copying the given object of the type \c scene_configuration.
    ///
    /// \param a a \c scene_configuration from which the new one is
    /// constructed.
    ///
    scene_configuration(const scene_configuration& a) = default;

    ///
    /// \brief Constructs an object of the type \c scene_configuration by
    /// moving the given object of the type \c scene_configuration.
    ///
    /// \param a a \c scene_configuration from which the new one is
    /// constructed.
    ///
    scene_configuration(scene_configuration&& a) = default;

    ///
    /// \brief Destructs an object of the type \c scene_configuration.
    ///
    ~scene_configuration() = default;

    ///
    /// \brief Assigns the given object of the type \c scene_configuration to
    /// this one by copying.
    ///
    /// \param a a \c scene_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration& operator=(const scene_configuration& a) = default;

    ///
    /// \brief Assigns the given object of the type \c scene_configuration to
    /// this one by moving.
    ///
    /// \param a a \c scene_configuration from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration& operator=(scene_configuration&& a) = default;
  
  private:
    ///
    /// \brief A vector which contains the system types of the systems which
    /// should create scenes for this configuration.
    ///
    std::vector<system_type> systems;
  };
} // namespace ode

#endif // !ODE_SCENES_SCENE_CONFIGURATION_H
