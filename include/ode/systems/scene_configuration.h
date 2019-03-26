//===----------------------- scene_configuration.h --------------*- C++ -*-===//
//
//                        Obliging Ode & Unsung Anthem
//
// This source file is part of the Obliging Ode and Unsung Anthem open source
// projects.
//
// Copyright (C) 2019 Antti Kivi
// All rights reserved
//
//===----------------------------------------------------------------------===//
//
///
/// \file scene_configuration.h
/// \brief The declaration of the type of the scene configurations.
/// \author Antti Kivi
/// \date 4 June 2018
/// \copyright Copyright (C) 2019 Antti Kivi
/// All rights reserved
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SCENE_CONFIGURATION_H
#define ODE_SYSTEMS_SCENE_CONFIGURATION_H

namespace ode
{
  ///
  /// \class scene_configuration
  /// \brief The type of the objects which hold the configurations of the
  /// scenes which determine how a scene is loaded and run.
  ///
  class scene_configuration
  {
  public:
    ///
    /// \brief Constructs an object of the type \c scene_configuration.
    ///
    scene_configuration() = default;

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
    virtual ~scene_configuration() = default;

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
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SCENE_CONFIGURATION_H
