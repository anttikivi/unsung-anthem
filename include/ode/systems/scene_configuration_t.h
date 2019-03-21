//===---------------------- scene_configuration_t.h -------------*- C++ -*-===//
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
/// \file scene_configuration_t.h
/// \brief The declaration of the type of the scene configuration wrappers.
/// \author Antti Kivi
/// \date 11 June 2018
/// \copyright Copyright (c) 2019 Antti Kivi
/// Licensed under GNU Affero General Public License v3.0
///
//
//===----------------------------------------------------------------------===//

#ifndef ODE_SYSTEMS_SCENE_CONFIGURATION_T_H
#define ODE_SYSTEMS_SCENE_CONFIGURATION_T_H

#include <memory>
#include <utility>

#include "ode/systems/scene_configuration.h"

namespace ode
{
  ///
  /// \class scene_configuration_t
  /// \brief The type of the objects which hold the scene configuration object
  /// implementations.
  ///
  class scene_configuration_t final
  {
  public:
    ///
    /// \brief Constructs an object of the type \c scene_configuration_t.
    ///
    scene_configuration_t() = default;

    ///
    /// \brief Constructs an object of the type \c scene_configuration_t.
    ///
    /// \tparam T the type of the configuration implementation.
    ///
    /// \param t the configuration implementation.
    ///
    template <typename T> scene_configuration_t(T t)
    : config_ptr{std::make_shared<T>(std::move(t))}
    {

    }

    ///
    /// \brief Constructs an object of the type \c scene_configuration_t by
    /// copying the given object of the type \c scene_configuration_t.
    ///
    /// \param a a \c scene_configuration_t from which the new one is
    /// constructed.
    ///
    scene_configuration_t(const scene_configuration_t& a) = default;

    ///
    /// \brief Constructs an object of the type \c scene_configuration_t by
    /// moving the given object of the type \c scene_configuration_t.
    ///
    /// \param a a \c scene_configuration_t from which the new one is
    /// constructed.
    ///
    scene_configuration_t(scene_configuration_t&& a) = default;

    ///
    /// \brief Destructs an object of the type \c scene_configuration_t.
    ///
    ~scene_configuration_t() = default;

    ///
    /// \brief Assigns the given object of the type \c scene_configuration_t to
    /// this one by copying.
    ///
    /// \param a a \c scene_configuration_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration_t& operator=(const scene_configuration_t& a) = default;

    ///
    /// \brief Assigns the given object of the type \c scene_configuration_t to
    /// this one by moving.
    ///
    /// \param a a \c scene_configuration_t from which this one is assigned.
    ///
    /// \return A reference to \c *this.
    ///
    scene_configuration_t& operator=(scene_configuration_t&& a) = default;

  private:
    ///
    /// \brief A pointer to the contained configuration implementation.
    ///
    std::shared_ptr<const scene_configuration> config_ptr;
  };

} // namespace ode

#endif // !ODE_SYSTEMS_SCENE_CONFIGURATION_T_H
